
/**
 *  Author :			Avishai Cohen
 *  Creation date :     16.02.2019
 *  Date last modified :
 * 						
 *  Description : 		dispatcher module, part of cdr billing system
 * 						dispatcher working-mode roles are:
 * 						1. to get cdrs lines via channel
 * 						2. parse cdr into cdr format
 * 						3. store send cdr's to storage modules
 * 
 **/
 
#ifndef __DISPATCH_H__
#define __DISPATCH_H__

#include "ops_container.h" 		/* OpCont */
#include "subs_container.h" 	/* SubCont */

typedef struct DispItems DispItems;

/** 
 * @brief This function structure that holdes aggregators
 * @param[in] _ops, _subs - pointers to aggregators
 * @return DispItems item on success, NULL on fail
 */
DispItems* Disp_Create(OpCont* _ops, SubCont* _subs);
/**
 * @brief recieving cdr's and inserting them to container, MT based 
 * @param	_dsp -structure that holdes aggregators
 * @return	NULL
 * 
 **/
void* Disp_Operate(void* _dsp);

#endif /* __DISPATCH_H__ */
