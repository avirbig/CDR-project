/**
 *  Author :			Avishai Cohen
 *  Creation date :     14.02.2019
 *  Date last modified :
 * 						
 *  Description : 		file monitoring API Polling Method
 **/

//struct dirent {
    //ino_t          d_ino;
    //off_t          d_off;       
    //unsigned short d_reclen;
    //unsigned char  d_type;      
    //char           d_name[256]; 
//};

#include "newfm.h"
#include "macros.h"
#include "channel.h"
#include "newfr.h"
#include "colors.h"

#include <unistd.h> 	/* fork */
#include <sys/types.h> 	/* pid_t*/
#include <sys/wait.h>	/* wait */
#include <dirent.h> 	/* scandir */
#include <stdlib.h> 	/* free */
#include <string.h> 	/* strstr */
#include <semaphore.h> /* sem_wait */
#include <fcntl.h> /* O_CREAT */


       /* STATIC FUNCTIONS */
static void File_DeAllocateScandDir(struct dirent **_fileList, int _numOfFiles);


FILE* File_Open(const char* _path)
{
	return fopen(_path, "r");
}

int File_Close(FILE* _fd)
{
	return fclose(_fd);
}

int File_Move(const char* _oldpath, const char* _newpath)
{
	return rename(_oldpath, _newpath);
}

static void File_DeAllocateScandDir(struct dirent **_fileList,int _numOfFiles)
{
	int i = 0;
	
	for (i = 0; i < _numOfFiles; ++i)
	{
	  free(_fileList[i]);
	}
	
	free(_fileList);
}

int File_ScanExecMove(const char* _execPath, const char* _ipath, const char* _wpath, const char* _fpath, int _maxRunning)
{
	struct dirent **fileList = NULL;
	int numOfFiles = 0, i, status;
	int totalFilesRead = 0;
	char* cdrOccurence = NULL;
	pid_t cpid;
	char startDir[MAX_FILE_NAME], workingDir[MAX_FILE_NAME], doneDir[MAX_FILE_NAME]; 
	char *childArgs[5];
	Msg_Buffer m;
	Channel* children = NULL;
	sem_t* maxRunning = NULL;
	
	maxRunning = sem_open(SEMAPHORE_NAME, O_CREAT, SEMAPHORE_PERMISSIONS, _maxRunning);
	
	children = Channel_Create(FILE_MONITOR_PATH, CHANNEL_DEFAULT_INT);
	if(!IS_VALID(children)) STDERR_PRINT("Channel Create Fail\n");
	
	childArgs[0] = (char*)_execPath;
	childArgs[4] = NULL;
	
	while(TRUE)
	{
		numOfFiles = scandir(_ipath, &fileList, NULL, alphasort); /* fm must be in initial dir ?? */
		if(IS_EQUAL(numOfFiles, -1))
		{
			STDERR_PRINT("scandir FAIL\n");
			break;
		}
		
		for(i = 2; i < numOfFiles; ++i)  /* FIRST TWO ARE . .. (IRRELEVANT) */
		{
			cdrOccurence = strstr(fileList[i]->d_name, ".cdr"); /* ONLY CDR FILES */
			if(!IS_VALID(cdrOccurence)) continue;
			++totalFilesRead;
			
			FULLPATH(startDir,_ipath,fileList[i]->d_name);
			FULLPATH(workingDir,_wpath,fileList[i]->d_name);
			FULLPATH(doneDir,_fpath,fileList[i]->d_name);
			
			printf("execPath %s\n", _execPath);
			
			childArgs[1] = startDir;
			printf("childArgs[0] %s\n", childArgs[0]);
			childArgs[2] = workingDir;
			childArgs[3] = doneDir;
			
			sem_wait(maxRunning);
			cpid = fork(); /* CHILD WILL PROCESS FILE*/
			if(IS_EQUAL(cpid,-1)) {STDERR_PRINT(RED "fork Fail\n" RESET); return -1;}
			else if(cpid == 0)	/*CHILD*/
			{
				printf("FORK SUCCESS\n");
				status = execvp( _execPath, childArgs);
				if(IS_EQUAL(status,-1)) {STDERR_PRINT(RED "execv Fail\n" RESET);}
				else printf("EXECV SUCCESS\n");
			}/* else if(cpid == 0) */
		}/* for(numOfFiles) */
		
		while(Channel_NumOfMessagesIn(children))
		{
			Channel_Recieve(children, &m, CHANNEL_DEFAULT_TYPE, MSG_SIZE);
			printf("child pid %d is released\n", m.m_int);
			waitpid(-1, NULL, 0);
		}
		
		File_DeAllocateScandDir(fileList, numOfFiles);
		sleep(3);
	}	/* while(TRUE) */
	
	Channel_Destroy(children);
	
	printf("totalFilesRead %d\n", totalFilesRead);  /* DEBUG */
	return totalFilesRead;
}
