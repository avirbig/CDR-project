/**
 *  Author :			Avishai Cohen
 *  Creation date : 	12.02.2019  
 *  Date last modified :
 * 						
 *  Description : 		Data Transfer API
 **/
#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <stddef.h> /* size_t */
#include "macros.h" 

typedef struct Channel Channel;

/**********************************************/
		/* MESSAGES STRUCT TYPES */
/**********************************************/
typedef struct Msg_Buffer{
	long 	m_type;
	int 	m_UserOption;
	int 	m_int;
	long 	m_long;
	char 	m_buffer[STR_SIZE];
}Msg_Buffer;
/**********************************************/


/**
 * 
 * @brief creates the channel
 * @param[in] - _fileName - full path to an existing file
 * @param[in] - _n - user choice
 * @return pointer to Channel, NULL - on error
 * 
 **/
Channel* Channel_Create(char* _fileName, int _n);
/**
 * 
 * @brief sends item into channel
 * @param[in] _c - pointer to channel
 * @param[in] _msg - pointer to message
 * @param[in] _msgSize - message size in bytes
 * @param[in] _msgType - message type (User Defined)
 * @return status
 * 
 **/
int Channel_Send(Channel* _c, void* _msg, size_t _msgSize, long _msgType);
/**
 * 
 * @brief recieves message from channel
 * @param[in] _c - pointer to channel
 * @param[out] _msg
 * @param[in] _msgSize - message size in bytes
 * @param[in] _msgType - message type (User Defined)
 * @return status
 * 
 **/
int Channel_Recieve(Channel* _c, void* _msg, long _msgType ,size_t _msgSize);
/**
 * 
 * @brief destroy channel
 * @param[in] _c - pointer to channel
 * @return status
 * 
 **/
int Channel_Destroy(Channel* _c);
/**
 * 
 * @brief Destroys allocated data, without destroying channel itself
 * @param[in] _c - pointer to channel
 * @return void
 * 
 **/
void Channel_Detach(Channel* _c);
/**
 * 
 * @brief number of current messages in channel
 * @param[in] _c - pointer to channel
 * @return number of current messages in channel, -1 on fail
 * 
 **/
size_t Channel_NumOfMessagesIn(Channel* _c);
/**
 * 
 * @brief maximum size message que can hold
 * @param[in] _c - pointer to channel
 * @return maximum size message que can hold, -1 on fail
 * 
 **/
size_t Channel_MaxTotalSizeInBytes(Channel* _c);
/**********************************************/
		/* MESSAGES PRINT = DEBUG */
/**********************************************/
void Channel_PrintMsg(Msg_Buffer* _m);

#endif /* __CHANNEL_H__ */
