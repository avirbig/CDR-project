/** 
 *  @file sub.h
 *  @brief Single Subscriber
 *			
 *  @details  
 *	@Time Created: 13.02.2019
 *  @author Avishai Cohen
 * 
 *  @bug 
 */

#ifndef __SUB_H__
#define __SUB_H__

#include <stddef.h> /* size_t */
#include "cdr.h" 	/* Cdr */

typedef struct Sub Sub;

typedef unsigned long Ulong;

/** 

 * @brief This program Creates a new Sub item
 * 
 * @param[in] _id - MCC/MNC tuple
 * @param[in] _name - Sub Brand Name, a string of maximum 64 chars
 * @returns pointer to Sub item on success, NULL on fail
 */
Sub* Sub_Create(Ulong _id);
/** 
 * @brief This program destroys Sub element created by Sub_Create
 * 
 * @param[in] _sub - pointer to Sub item
 * @returns void
 */
void Sub_Destroy(void* _sub);
/** 
 * @brief This program Update values of single subscriber according to Cdr Type
 * 
 * @param[in] _sub - pointer to Sub item
 * @param[in] _c - void pointer to Cdr
 * @returns void
 */
int Sub_Update(void* _sub, void* _c);
/** 
 * @brief This program extract data from subscriber as a string
 * 
 * @param[in] _sub - pointer to Sub item
 * @param[out] _line - pointer to buffer to store string into
 * @returns num of chars printed in string
 */
int Sub_GetData(void* _sub, void* _line);
/** 
 * @brief reset all values of subscriber
 * 
 * @param[in] _sub - pointer to Sub item
 * @returns  void
 */
void Sub_Reset(Sub* _sub);
/*****************************************************************************/
					/* GET VALUES FUNCS */
/*****************************************************************************/
/** 
 * @brief retrievs address of subscriber id in order to be stored as value in aggregator
 * 
 * @param[in] _sub - pointer to Sub item
 * @returns pointer to subscriber id
 */
Ulong* Sub_GetIdAddres(Sub* _sub);
/*****************************************************************************/
					/* PRINTING VALUES FUNCS */
/*****************************************************************************/
void Sub_PrintValues(Sub* _sub);


#endif /* __SUB_H__ */
