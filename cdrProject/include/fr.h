/**
 *  Author :			Avishai Cohen
 *  Creation date :     10.02.19
 *  Date last modified :
 * 						
 *  Description : 		file reading API Polling Method
 **/
#ifndef __FR_H__
#define __FR_H__

typedef enum{
	FR_SUCCESS,
	FR_ERROR = -1
}Fh_Status;


/** 
 * @brief This program sets the enviroment for file reading
 * 
 * @param[in] void
 * @returns void pointer to channel to send data through it
 */
void* FR_Init(void);

/** 
 * @brief This program reads line, and send it via channel
 * 
 * @param[in] _fd - file descriptor
 * @param[in] _c - channel to send through
 * @returns void* as num of line been read, (void*) -1 as fail
 */
void* FR_ReadAndSend(void* _fd, void* _c);

#endif /* #ifndef __FR_H__ */
