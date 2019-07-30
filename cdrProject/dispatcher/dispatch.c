/**
 *  Author :			Avishai Cohen
 *  Creation date :     16.02.2019
 *  Date last modified :
 * 						
 *  Description : 		dispatcher module, part of cdr billing system
 * 						the dispatcher works in based on multi-thread enviroment
 * 						for concurency in a way that every thread is responsible for
 * 						single cdr recieved via channel
 * 						choosing MT upon MP because storage of accumulated information is shared
 * 						by all threads.
 **/

#include "macros.h"
#include "channel.h"
#include "cdr.h"
#include "operator.h"
#include "sub.h"
#include "dispatch.h"

#include <pthread.h> 		/* pthread_create */
#include <unistd.h> 		/* sleep */
#include <stdlib.h> 		/* malloc */


struct DispItems{
	Channel* m_channel;
	OpCont* m_opcont;
	SubCont* m_subcont;
}; 


DispItems* Disp_Create(OpCont* _ops, SubCont* _subs)
{
	DispItems* dsp = NULL;
	
	if(!IS_VALID(_ops) || !IS_VALID(_subs))
	{
		STDERR_PRINT("AGGREGATORES NULL Fail\n");
		return NULL;
	}
	
	dsp = malloc(sizeof(DispItems));
	if(!IS_VALID(dsp))
	{
		STDERR_PRINT("QM ALLOCATION FAIL Fail\n");
		return NULL;
	}
	
	dsp->m_opcont = _ops;
	dsp->m_subcont = _subs;
	dsp->m_channel = Channel_Create(DISPATCHER_PATH, CHANNEL_DEFAULT_INT);
	if(!IS_VALID(dsp->m_channel))
	{
		STDERR_PRINT("Channel Create Fail\n");
		free(dsp);
		return NULL;
	}
	
	return dsp;
}

static void* Disp_RecieveAnsStoreCdr(void* _args)
{
	int status;
	Cdr* cdr  = NULL;
	DispItems* args = _args;
	Msg_Buffer m;
	
	m.m_type = CHANNEL_DEFAULT_TYPE;
	
	status = Channel_Recieve(args->m_channel, &m, CHANNEL_DEFAULT_TYPE, MSG_SIZE);
	if(IS_EQUAL(status, -1)) STDERR_PRINT("Channel Recieve Fail\n");
	printf("CDR LINE: %s\n", m.m_buffer);
	
	cdr = Cdr_Create(m.m_buffer);
	if(!IS_VALID(cdr)) STDERR_PRINT("Cdr_Create Fail\n");
	status = OpCont_Update(args->m_opcont, cdr);
	if(!IS_EQUAL(status, OPCONT_SUCCESS)) STDERR_PRINT("OpCont_Update Fail\n");
	status = SubCont_Update(args->m_subcont, cdr);
	if(!IS_EQUAL(status, SUBCONT_SUCCESS)) STDERR_PRINT("SubCont_Update Fail\n");
			
	return NULL;
} 

void* Disp_Operate(void* _dsp)
{
	int status;
	size_t status1;
	DispItems* dsp = _dsp;
	
	while(TRUE)
	{
		while(Channel_NumOfMessagesIn(dsp->m_channel))
		{
			pthread_t reciever;
			
			status = pthread_create(&reciever, NULL, Disp_RecieveAnsStoreCdr, dsp);
			if(!IS_EQUAL(status, 0)) STDERR_PRINT("dsp pthread_create Fail\n");
			
			status = pthread_join(reciever, NULL);
			if(!IS_EQUAL(status, 0)) STDERR_PRINT("dsp pthread_join Fail\n");
			
			//sleep(1);
		}
		
		/* DEBUG */
		status1 = OpCont_PrintAll(dsp->m_opcont);
		printf("OpCont_PrintAll status %ld\n",status1);
		status1 = SubCont_PrintAll(dsp->m_subcont);
		printf("SubCont_PrintAll status %ld\n",status1);
		
		sleep(20);
	}
	
	Channel_Destroy(dsp->m_channel);
	
	return NULL;
}
