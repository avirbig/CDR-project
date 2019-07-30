/**
 *  Author :			Avishai Cohen
 *  Creation date :     18.02.2019
 *  Date last modified :
 * 						
 *  Description : 		query manager, interacts with many users
 **/

#include "ui.h"
#include "channel.h"
#include "ops_container.h"
#include "macros.h"
#include "cdr.h"
#include "qm.h"
#include "colors.h"

#include <stdio.h> 			/* printf */
#include <pthread.h> 		/* pthread_create */
#include <stdlib.h> 		/* malloc */
#include <unistd.h> 		/* sleep */
#include <string.h>		/* memset */


struct QMItems{
	SubCont* 	m_subcont;
	OpCont* 	m_opcont;
	Channel* 	m_channel;
	char 		m_outPath[STR_SIZE];
};

typedef struct ServiceArgs{
	SubCont* 	m_subcont;
	OpCont* 	m_opcont;
	Channel* 	m_channel;
	long 		m_type;
	char 		m_outPath[STR_SIZE];
}ServiceArgs;

QMItems* QM_Create(OpCont* _ops, SubCont* _subs, const char* _path)
{
	QMItems* qm = NULL;
	
	if(!IS_VALID(_ops) || !IS_VALID(_subs))
	{
		STDERR_PRINT("AGGREGATORES NULL Fail\n");
		return NULL;
	}
	
	qm = malloc(sizeof(QMItems));
	if(!IS_VALID(qm))
	{
		STDERR_PRINT("QM ALLOCATION FAIL Fail\n");
		return NULL;
	}
	
	qm->m_opcont = _ops;
	qm->m_subcont = _subs;
	strcpy(qm->m_outPath, _path);
	qm->m_channel = Channel_Create(UI_PATH, CHANNEL_QM_INT);
	if(!IS_VALID(qm->m_channel))
	{
		STDERR_PRINT("Channel Create Fail\n");
		free(qm);
		return NULL;
	}
	
	return qm;
}

static void QM_GetQuery(Msg_Buffer *_msg, OpCont* _ops,  SubCont* _subs, const char* _path)
{
	int status;
	
	switch(_msg->m_UserOption)
	{
		case SINGLE_SUBSCRIBER_REPORT:
			status = SubCont_GetSubscriberData(_subs, _msg->m_long, _msg->m_buffer);
			if(!IS_EQUAL(status, SUBCONT_SUCCESS)) STDERR_PRINT("SubCont_GetSubscriberData Fail\n");
		break;
		
		case SINGLE_OPERATOR_REPORT:
			status = OpCont_GetOperatorData(_ops, _msg->m_int, _msg->m_buffer);
			if(!IS_EQUAL(status, OPCONT_SUCCESS)) STDERR_PRINT("OpCont_GetOperatorData Fail\n");
		break;
		
		case ALL_SUBSCRIBERS_REPORT:
			SubCont_PrintAllToFile(_subs, _path);
			strcpy( _msg->m_buffer, GREEN "ALL_SUBSCRIBERS_REPORT is PRINTED TO FILE\n" RESET);
		break;

		case ALL_OPERATORS_REPORT:
			OpCont_PrintAllToFile(_ops, _path);
			strcpy( _msg->m_buffer, GREEN "ALL_OPERATORS_REPORT is PRINTED TO FILE\n" RESET);
		break;

		case ALL_DATA_REPORT:
			SubCont_PrintAllToFile(_subs, _path);
			OpCont_PrintAllToFile(_ops, _path);
			strcpy( _msg->m_buffer, GREEN "ALL_DATA_REPORT is PRINTED TO FILE\n" RESET);
		break;
		
		default:
			STDERR_PRINT("INVALID INPUT Fail\n");
		break;
	}
}

static void* QM_Service(void* _args)
{
	ServiceArgs* args = _args;
	Msg_Buffer msgRcv, msgSend;
	int status;
	
	msgRcv.m_type = args->m_type;
	msgSend.m_type = args->m_type * 2;
	
	args->m_channel = Channel_Create(UI_PATH, args->m_type);
	if(!IS_VALID(args->m_channel))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return NULL;
	}
	
	while(TRUE)
	{
		memset(msgRcv.m_buffer,0,STR_SIZE);
		printf("%ld messages in channel \n", Channel_NumOfMessagesIn(args->m_channel));	
		status = Channel_Recieve(args->m_channel, &msgRcv, msgRcv.m_type, MSG_SIZE);
		if(IS_EQUAL(status, -1)) STDERR_PRINT("Channel Recieve Fail\n");
		printf("USER OPTION: %d\n", msgRcv.m_UserOption); 			/* DEBUG */
		
		if(IS_EQUAL(msgRcv.m_UserOption, EXIT)) 
		{
			printf("EXIT MESSAGE RECIEVED VIA %ld CHANNEL\n", msgRcv.m_type);
			break;
		}
		
		msgSend.m_UserOption = msgRcv.m_UserOption;
		msgSend.m_int = msgRcv.m_int;
		msgSend.m_long = msgRcv.m_long;
		memset(msgSend.m_buffer,0,STR_SIZE);
		
		QM_GetQuery(&msgSend, args->m_opcont, args->m_subcont, args->m_outPath);
		
		status = Channel_Send(args->m_channel, &msgSend, MSG_SIZE, msgSend.m_type);
		if(IS_EQUAL(status, -1)) 
		{
			STDERR_PRINT("Channel SEND Fail\n");
			continue;
		}
		
		sleep(1);
	}
	
	return NULL;
}

void* QM_Operate(void* _qm)
{
	int status;
	Msg_Buffer msg;
	QMItems* qm = _qm;
	
	while(TRUE)
	{
		pthread_t service;
		ServiceArgs args;
		
		status = Channel_Recieve(qm->m_channel, &msg, CHANNEL_ALL_TYPES, MSG_SIZE);
		if(IS_EQUAL(status, -1)) STDERR_PRINT("Channel Recieve Fail\n");
		printf(GREEN "MSG TYPE: %ld\n" RESET, msg.m_type); 			/* DEBUG */
		printf("%s\n", msg.m_buffer); 					/* DEBUG */
		
		status = Channel_Send(qm->m_channel, &msg, MSG_SIZE, msg.m_type);
		if(IS_EQUAL(status, -1)) 
		{
			STDERR_PRINT("Channel SEND Fail\n");
			continue;
		}
		
		args.m_opcont = qm->m_opcont;
		args.m_subcont = qm->m_subcont;
		args.m_type = msg.m_type;
		strcpy(args.m_outPath, qm->m_outPath);
		
		status = pthread_create(&service, NULL, QM_Service, &args);
		if(!IS_EQUAL(status, 0)) STDERR_PRINT("pthread_create Fail\n");
		
		status = pthread_detach(service);
		if(!IS_EQUAL(status, 0)) STDERR_PRINT("pthread_detach Fail\n");
	}
	
	return NULL;
}



