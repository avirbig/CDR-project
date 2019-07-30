/*
 * ctest.c
 * 
 * Copyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This is Test for channel.c module 
 * 
 */

#include "channel.h"
#include <stdio.h>
#include <string.h>

#define STDERR_PRINT(STR) fprintf(stderr,STR)
#define IS_VALID(X) ((X) != NULL)

int main(void)
{
	int status;
	size_t size = 0;
	Channel* c = NULL;

	char opData[300];
	char cdrLine[300] = "292929292922222|292929292922222|3333|Cellcom Israel|42502|MTC|DD/MM/YYYY|HH:MM:SS|3000|2.3|1.4|292929292922222|42503";

	c = Channel_Create(1);
	if(!IS_VALID(c))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return 1;
	}
	
	status = Channel_Send(c, cdrLine, sizeof(cdrLine));
	if(status) STDERR_PRINT("Channel Send Fail\n");
	
	size = Channel_NumOfMessagesIn(c);
	printf("NUM OF MESSAGES IN CHANNEL: %ld\n", size);
	
	status = Channel_Recieve(c, opData, 1, sizeof(cdrLine));
	if(status == -1) STDERR_PRINT("Channel Recieve Fail\n");
	
	printf("CDR LINE: %s\n", cdrLine);
	
	size = Channel_NumOfMessagesIn(c);
	printf("NUM OF MESSAGES IN CHANNEL: %ld\n", size);
	
	size = Channel_MaxTotalSizeInBytes(c);
	printf("MAX BYTES: %ld\n", size);

	status = Channel_Destroy(c);
	if(status) STDERR_PRINT("Channel Destroy Fail \n");
	
	return 0;
}





