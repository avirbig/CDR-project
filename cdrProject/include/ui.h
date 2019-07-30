/**
 *  Author :			Avishai Cohen
 *  Creation date :     16.02.2019
 *  Date last modified :
 * 						
 *  Description : 		user interface with cdr charging system
 **/

#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>  /* printf */

typedef enum User_Option{
	EXIT = 0,
	SINGLE_SUBSCRIBER_REPORT = 1,
	SINGLE_OPERATOR_REPORT,
	ALL_SUBSCRIBERS_REPORT,
	ALL_OPERATORS_REPORT,
	ALL_DATA_REPORT,
	SYSTEM_PAUSE,
	SYSTEM_RESUME,
	SYSTEM_SHUTDOWN
}User_Option;



typedef unsigned long Ulong;
/** 
 * @brief print menu for system query, pause, resume shutdown
 * 
 * @param[in] void
 * @returns void
 */
void UserPrintMenu(void);
/********************************************************************/
/** 
 * @brief function to get char from user
 * 
 * @param[in] void
 * @returns char item given by user
 * @warning: "garbage in - garbage out"
 */
char User_GetChar(void);
/********************************************************************/
/** 
 * @brief function to get int from user
 * 
 * @param[in] void
 * @returns int item given by user
 * @warning: "garbage in - garbage out"
 */
int User_GetInt(void);
/********************************************************************/
/** 
 * @brief function to get float from user
 * 
 * @param[in] void
 * @returns float item given by user
 * @warning: "garbage in - garbage out"
 */
float User_GetFloat(void);
/********************************************************************/
/** 
 * @brief function to get string from user
 * 
 * @param[in] void
 * @returns string item given by user
 * @warning: max chars are STR_SIZE - 1
 */
char* User_GetStr(char *_s);
/********************************************************************/
/** 
 * @brief function to get unsigned long from user
 * 
 * @param[in] void
 * @returns unsigned long item given by user
 * @warning: "garbage in - garbage out"
 */
Ulong User_GetUnsignedLong(void);
/********************************************************************/

#endif
