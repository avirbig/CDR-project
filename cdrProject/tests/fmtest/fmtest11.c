/*
 * fmtest11.c
 * 
 * Copyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This is Test for fm.c module 
 * 
 */

#include "channel.h"
#include "macros.h"

#include <stdio.h>
//#include <string.h>	
#include <unistd.h> /* sleep */


int main(void)
{
	int status;
	Channel* c = NULL;
	char opData[300];

	c = Channel_Create(DISPATCHER_PATH, CHANNEL_INT);
	if(!IS_VALID(c))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return 1;
	}
	
	while(Channel_NumOfMessagesIn(c))
	{
		status = Channel_Recieve(c, opData, 1, sizeof(opData));
		if(status == -1) STDERR_PRINT("Channel Recieve Fail\n");
		printf("CDR LINE: %s\n", opData);	
		sleep(1);
	}
	
	status = Channel_Destroy(c);
	if(status) STDERR_PRINT("Channel Destroy Fail \n");
	
	return 0;
}





