/**
 *  Author :			Avishai Cohen
 *  Creation date :     13.02.2019
 *  Date last modified :
 * 						
 *  Description : 		file handling executed by file monitor by fork and execvp
 * 						this profram connects to channel, reads line by line
 * 						and sends the line by channel
 * 						in the end it sends signal to its sends a msg through channel  to parent
 * 						process to wait for it, and increment named semaphore 
 **/
 

#include "channel.h" /* Channel_Send */
#include "macros.h"
#include "colors.h"
#include "newfm.h"

#include <stdio.h> 		/* printf */
#include <string.h> 	/* strcpy */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>		/* getpid */
#include <signal.h>		/* signal */
#include <sys/wait.h>	/*	wait */
#include <semaphore.h> /* sem_post */
#include <fcntl.h> /* O_CREAT */

	
int main(int argc, char* argv[])
{
	FILE* fd = NULL;
	Channel* c = NULL;
	Channel* ending = NULL;
	int status;
	Msg_Buffer m;
	char startDir[MAX_FILE_NAME], workingDir[MAX_FILE_NAME], doneDir[MAX_FILE_NAME];
	pid_t mypid;
	sem_t* maxRunning = NULL;

	maxRunning = sem_open(SEMAPHORE_NAME, O_CREAT, SEMAPHORE_PERMISSIONS, 0);

	mypid = getpid();
	
	printf(GREEN "CHILD PROCESS %d IS RUNNING\n" RESET, mypid); /* DEBUG */
	
	strcpy(startDir, argv[1]);
	strcpy(workingDir, argv[2]);
	strcpy(doneDir, argv[3]);
	
	c = Channel_Create(DISPATCHER_PATH, CHANNEL_DEFAULT_INT);
	if(!IS_VALID(c))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return 1;
	}
	
	status = File_Move(startDir, workingDir);
	if(IS_EQUAL(status, -1)) STDERR_PRINT("File_Move Fail \n");
	
		fd = File_Open(workingDir);
		if(fd == NULL) {STDERR_PRINT("File Open Fail\n"); return -1;}
	
			m.m_type = CHANNEL_DEFAULT_TYPE;
			
			while(fgets(m.m_buffer, STR_SIZE, fd))
			{
				status = Channel_Send(c, &m, MSG_SIZE, CHANNEL_DEFAULT_TYPE);
				if(IS_EQUAL(status, -1)) break;
			}

		status = File_Close(fd);
		if(status) STDERR_PRINT("fclose Fail \n");
	
	status = File_Move(workingDir, doneDir);
	if(IS_EQUAL(status, -1)) {STDERR_PRINT("File_Move Fail \n"); return -1;} 

	Channel_Detach(c);
	
	ending = Channel_Create(FILE_MONITOR_PATH, CHANNEL_DEFAULT_INT);
	if(!IS_VALID(ending))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return 1;
	}
	
	m.m_int = mypid;
	
	status = Channel_Send(ending, &m, MSG_SIZE, CHANNEL_DEFAULT_TYPE);
	if(IS_EQUAL(status, -1)) STDERR_PRINT("CHILD END MSG FAIL Fail\n");
	
	Channel_Detach(ending);
	sem_post(maxRunning);
	
	return 0;
}
