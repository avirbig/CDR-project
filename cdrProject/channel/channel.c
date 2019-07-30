/**
 *  Author :			Avishai Cohen
 *  Creation date : 	13.02.2019  
 *  Date last modified :
 * 						
 *  Description : 		Channel implementation using Msg_BufferQueue
 **/

#include "msgQ.h"
#include "channel.h"
#include "macros.h"

#include <sys/msg.h> 	/* IPC_CREAT */
#include <string.h> 	/* strcpy */
#include <stdlib.h> 	/* malloc */
#include <stdio.h> 		/* printf */
 

#define PREMISIONS 0664  
#define MSGQ_CREATE_FLAG IPC_CREAT 
#define SEND_FLAG 0
#define MSG_TYPE 1

struct Channel{
	int m_msgId; 
};

Channel* Channel_Create(char* _fileName, int _n) 
{
	Channel* c = NULL;
	key_t key = 0;
	
	c = malloc(sizeof(Channel));
	if(!IS_VALID(c))
	{
		return NULL;
	}
	
	key = MsgQ_GetKey(_fileName, _n);
	STDERR_IS_EQUAL_STATUS(key, -1, "key generation fail\n");
	if(IS_EQUAL(key, -1))
	{
		free(c);
		return NULL;
	}
	
	c->m_msgId = MsgQ_Create(key, PREMISIONS | MSGQ_CREATE_FLAG);
	STDERR_IS_EQUAL_STATUS(c->m_msgId, -1, "Channel creation fail\n");
	if(IS_EQUAL(c->m_msgId, -1))
	{
		free(c);
		return NULL;
	}
	
		/* DEBUG */
		printf("_c->m_msgId %d\n", c->m_msgId);
	
	return c;
}

int Channel_Destroy(Channel* _c)
{
	int status;
	
	if(!IS_VALID(_c))
	{
		return -1;
	}
	
	status = MsgQ_Destroy(_c->m_msgId);
	free(_c);
	
	return status;
}

void Channel_Detach(Channel* _c)
{
	if(!IS_VALID(_c))
	{
		return;
	}
	
	free(_c);
}

int Channel_Send(Channel* _c, void* _msg, size_t _msgSize, long _msgType)
{
	if(!IS_VALID(_c))
	{
		return -1;
	}
	
	return MsgQ_Send(_c->m_msgId, _msg, _msgSize, MSG_NOERROR);
}

int Channel_Recieve(Channel* _c, void* _msg, long _msgType ,size_t _msgSize)
{
	if(!IS_VALID(_c))
	{
		return -1;
	}
	
	return (int) MsgQ_Recieve(_c->m_msgId,_msg, _msgSize, _msgType, MSG_NOERROR);
}

size_t Channel_NumOfMessagesIn(Channel* _c)
{
	if(!IS_VALID(_c))
	{
		return -1;
	}
	
	return MsgQ_NumOfMsgInQ(_c->m_msgId);
}

size_t Channel_MaxTotalSizeInBytes(Channel* _c)
{
	if(!IS_VALID(_c))
	{
		return -1;
	}
	
	return MsgQ_MaxBytes(_c->m_msgId);
}

void Channel_PrintMsg(Msg_Buffer* _m)
{
	printf("TYPE: %ld \n",_m->m_type);
	printf("UOP : %d  \n",_m->m_UserOption);
	printf("INT : %d  \n",_m->m_int);
	printf("LONG: %ld \n",_m->m_long);
	printf("BUFF: %s  \n",_m->m_buffer);
}
