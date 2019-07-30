/**
 *  Author :			Avishai Cohen
 *  Creation date :     10.02.19
 *  Date last modified :
 * 						
 *  Description : 		operator API
 **/
#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include <stddef.h> /* size_t */
#include "cdr.h" 	/* Cdr */

typedef struct Op Op;

typedef unsigned long Ulong;

/** 

 * @brief This program Creates a new Op item
 * 
 * @param[in] _id - MCC/MNC tuple
 * @param[in] _name - Op Brand Name, a string of maximum 64 chars
 * @returns pointer to Op item on success, NULL on fail
 */
Op* Op_Create(size_t _id, char* _name);
/** 
 * @brief This program destroys Op element created by Op_Create
 * 
 * @param[in] _op - pointer to Op item
 * @returns void
 */
void Op_Destroy(void* _op);
/** 
 * @brief This program Update values of single operator according to Cdr Type
 * 
 * @param[in] _op - pointer to Op item
 * @param[in] _c - void pointer to Cdr
 * @returns void
 */
int Op_Update(void* _op, void* _c);

int Op_GetData(void* _op, void* _line);

void Op_Reset(Op* _op);
/*****************************************************************************/
					/* GET VALUES FUNCS */
/*****************************************************************************/
char* Op_GetOpName(Op* _op);

size_t Op_GetID(Op* _op);

Ulong Op_GetInDuration(Op* _op);

Ulong Op_GetOutDuration(Op* _op);

Ulong Op_GetInSMS(Op* _op);

Ulong Op_GetOutSMS(Op* _op);
/*****************************************************************************/
					/* PRINTING VALUES FUNCS */
/*****************************************************************************/
void Op_PrintValues(Op* _op);


#endif /* __OPERATOR_H__ */
