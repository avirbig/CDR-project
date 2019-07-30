/*
 * frtest.c
 * 
 * Copyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This is Test for fr.c module 
 * the module consists of:
 * 1. opening channel for sending files (FR_Init)
 * 2. opening file to read from
 * 3. reading all lines through channel
 * 4. getting all lines via channel
 * 
 */

#include "channel.h"
#include "fr.h"
#include <stdio.h>
#include <string.h>

#define STDERR_PRINT(STR) fprintf(stderr,STR)
#define IS_VALID(X) ((X) != NULL)

int main(void)
{
	int status;
	FILE* fd = NULL;
	Channel* c = NULL;
	char opData[300];

	c = Channel_Create(1);
	if(!IS_VALID(c))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return 1;
	}
	
	fd = fopen("example.cdr", "r");
	if(fd == NULL) STDERR_PRINT("File Open Fail\n");
	
	FR_ReadAndSend(fd, c);
	
	while(Channel_NumOfMessagesIn(c))
	{
		status = Channel_Recieve(c, opData, 1, sizeof(opData));
		if(status == -1) STDERR_PRINT("Channel Recieve Fail\n");
		printf("CDR LINE: %s\n", opData);
	}
	
	status = fclose(fd);
	if(status) STDERR_PRINT("fclose Fail \n");

	status = Channel_Destroy(c);
	if(status) STDERR_PRINT("Channel Destroy Fail \n");
	
	return 0;
}





