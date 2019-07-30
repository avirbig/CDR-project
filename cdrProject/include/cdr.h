/**
 *  Author :			Avishai Cohen
 *  Creation date :     10.02.19
 *  Date last modified :
 * 						
 *  Description : 		CDR - Charging Data Record API
 **/
#ifndef __CDR_H__
#define __CDR_H__

#include <stddef.h> /* size_t */

typedef struct Cdr Cdr;

typedef unsigned long Ulong;

typedef enum{
	MOC, 	/*outgoing voice call*/
	MTC, 	/*incoming voice call*/
	SMSMO, 	/*outgoing message*/
	SMSMT, 	/*incoming message*/
	GPRS 	/*internet*/
}Call_Type;

/** 
 * @brief Creates CDR element from line 
 * 
 * @param[in] _line - string to generate line from
 * @returns Cdr pointer on success, NULL on fail
 */
Cdr* Cdr_Create(char* _line);
/** 
 * @brief destroys cdr element created by Cdr_Create
 * 
 * @param[in] _fd - pointer to file
 * @returns void 
 */
void Cdr_Destroy(Cdr* _c);
/*****************************************************************************/
						/* GET VALUES FUNCS */
/*****************************************************************************/
/** 
 * @brief Functions to extract data from Cdr element
 * 
 * @param[in] _c - pointer to Cdr
 * @returns depends on data type
 */

Ulong Cdr_GetIMSI(Cdr* _c);

Ulong Cdr_GetMSISDN(Cdr* _c);

Ulong Cdr_GetIMEI(Cdr* _c);

char* Cdr_GetOpName(Cdr* _c);

size_t Cdr_GetOpId(Cdr* _c);

Call_Type Cdr_GetCallType(Cdr* _c);

char* Cdr_GetDate(Cdr* _c);

char* Cdr_GetTime(Cdr* _c);

Ulong Cdr_GetDuration(Cdr* _c);

float Cdr_GetDownload(Cdr* _c);

float Cdr_GetUpload(Cdr* _c);

Ulong Cdr_GetPartyMSISDN(Cdr* _c);

size_t Cdr_GetPartyOperator(Cdr* _c);

#endif /* #ifndef __CDR_H__ */
