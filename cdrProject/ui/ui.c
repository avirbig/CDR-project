/**
 *  Author :			Avishai Cohen
 *  Creation date :     16.02.2019
 *  Date last modified :
 * 						
 *  Description : 		user interface with cdr charging system
 * 						in working interface
 * 						request messages typw is user pid
 * 						recieved messages are in type user pid * 2
 **/

#include "ui.h"
#include "channel.h"
#include "macros.h"
#include "colors.h"

#include <string.h> 	/* sprinf */
#include <sys/types.h> 	/* pid_t */
#include <unistd.h>		/* getpid */

#define TYPE_ERROR 10


/********************************************************************/
				/* STATIC FUNCS */
static int User_GetMCCMNC(void);
static Ulong User_GetUserMSISDN(void);

/********************************************************************/
void User_PrintMenu(void)
{
	printf("\nCHOOSE OPTION:\n"
			"[0] - EXIT						\n"
			"[1] - SINGLE SUBSCRIBER REPORT	\n"
			"[2] - SINGLE OPERATOR REPORT	\n"
			"[3] - ALL SUBSCRIBERS REPORT	\n"
			"[4] - ALL OPERATORS REPORT		\n"
			"[5] - ALL DATA REPORT			\n"
			"[6] - SYSTEM PAUSE 			\n"
			"[7] - SYSTEM RESUME 			\n"
			"[8] - SYSTEM SHUTDOWN 			\n\n"
			);
}
/********************************************************************/
static void User_MsgVariables(Msg_Buffer* _msg)
{
	switch(_msg->m_UserOption)
	{
		case SINGLE_SUBSCRIBER_REPORT:
			_msg->m_long = User_GetUserMSISDN();
		break;
		
		case SINGLE_OPERATOR_REPORT:
			_msg->m_int = User_GetMCCMNC();
		break;
		
		case ALL_SUBSCRIBERS_REPORT:
		break;
		
		case ALL_OPERATORS_REPORT:
		break;
		
		case ALL_DATA_REPORT:
		break;
		
		case SYSTEM_PAUSE:
			printf("Sorry Unavaliable at the time\n");
		break;
		
		case SYSTEM_RESUME:
			printf("Sorry Unavaliable at the time\n");
		break;
		
		case SYSTEM_SHUTDOWN:
			printf("Sorry Unavaliable at the time\n");
		break;
		
		default:
		break;
	}
}
/********************************************************************/
char User_GetChar(void)
{
	char ch;
	
	printf("ENTER CHAR:");
	scanf("%c", &ch);
	getchar();
	
	return ch;
}
/********************************************************************/
int User_GetInt(void)
{
	int num;
	
	printf("ENTER INT:");
	scanf("%d", &num);
	getchar();
	
	return num;
}
/********************************************************************/
static int User_GetMCCMNC(void)
{
	int num;
	
	printf("ENTER MCC/MNC of Operator:");
	scanf("%d", &num);
	getchar();
	
	return num;
}
/********************************************************************/
float User_GetFloat(void)
{
	float num;
	
	printf("ENTER FLOAT:");
	scanf("%f", &num);
	getchar();
	
	return num;
}
/********************************************************************/
char* User_GetStr(char *_s)
{
	char str[STR_SIZE];
	
	printf("ENTER STR:");
	scanf("%[^\n]s", str);
	getchar();
	
	strcpy(_s, str);
	return _s;
}
/********************************************************************/
size_t User_GetSize_t(void)
{
	size_t l;
	
	scanf("%ld", (long*)&l);
	getchar();
	
	return l;
}
/********************************************************************/
Ulong User_GetUnsignedLong(void)
{
	Ulong l;
	
	scanf("%ld", (long*)&l);
	getchar();
	
	return l;
}
/********************************************************************/
static Ulong User_GetUserMSISDN(void)
{
	Ulong l;
	
	printf("ENTER User MSISDN:");
	scanf("%ld", (long*)&l);
	getchar();
	
	return l;
}
/********************************************************************/
Channel* User_FirstContact(void)
{
	int status;
	pid_t mypid;
	Channel *channel = NULL;
	Msg_Buffer msg;
	
	channel = Channel_Create(UI_PATH, CHANNEL_QM_INT);
	if(!IS_VALID(channel))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return NULL;
	}
	
	mypid = getpid();
	msg.m_type = mypid;
	sprintf(msg.m_buffer, BLUE "user with pid = %d initiating contact" RESET, mypid);
	
	status = Channel_Send(channel, &msg, MSG_SIZE, (long)mypid);
	if(IS_EQUAL(status, -1)) STDERR_PRINT("Channel_Send Fail\n");
	
	status = Channel_Recieve(channel, &msg, (long)mypid, MSG_SIZE);
	if(IS_EQUAL(status, -1)) STDERR_PRINT("Channel Recieve Fail\n");
	printf("newInt: %d\n", msg.m_int); /* DEBUG */
	
	Channel_Detach(channel);
	channel = Channel_Create(UI_PATH, msg.m_type);
	if(!IS_VALID(channel))
	{
		STDERR_PRINT("Channel Create Fail\n");
		return NULL;
	}
	
	return channel;
}

void User_WorkingInterface(Channel* _pChannel, pid_t _mypid)
{
	int status;
	Msg_Buffer msgRcv, msgSend;
	
	msgSend.m_type = _mypid;
	msgRcv.m_type = _mypid * 2;
	msgSend.m_UserOption = 1;
	User_PrintMenu();
	
	while(TRUE)
	{
		while((msgSend.m_UserOption =  User_GetInt()))
		{
			if(IS_OPTION_INVALID(msgSend.m_UserOption))
			{
				STDERR_PRINT("InValid Option\n");
				User_PrintMenu();
				 continue;
			}
			else break;
		}
		
		User_MsgVariables(&msgSend);
		
		memset(msgSend.m_buffer,0,STR_SIZE);
		status = Channel_Send(_pChannel, &msgSend, MSG_SIZE,msgSend.m_type);
		if(IS_EQUAL(status, -1)) STDERR_PRINT("Channel_Send Fail\n");
		
		if(!msgSend.m_UserOption) break;
		
		memset(msgRcv.m_buffer,0,STR_SIZE);
		printf("%ld messages in channel \n", Channel_NumOfMessagesIn(_pChannel));	/* DEBUG */
		status = Channel_Recieve(_pChannel, &msgRcv, msgRcv.m_type, MSG_SIZE);
		if(IS_EQUAL(status, -1)) STDERR_PRINT("Channel Recieve Fail\n");
		printf("recieved info: %s\n", msgRcv.m_buffer);	
		
	}
	
	Channel_Destroy(_pChannel);
}

int main(void)
{
	Channel* c = NULL;
	pid_t mypid = getpid();
	
	c = User_FirstContact();
	User_WorkingInterface(c, mypid);
	
	return 0;
}









