/**
 *  Author :			Avishai Cohen
 *  Creation date :     18.02.2019
 *  Date last modified :
 * 						
 *  Description : 		query manager, interacts with many users
 **/

#ifndef __QM_H__
#define __QM_H__

#include "subs_container.h"
#include "ops_container.h"

typedef struct QMItems QMItems;

/** 
 * @brief This function structure that holdes aggregators
 * @param[in] _ops, _subs - pointers to aggregators
 * @param[in] _path - path for output reports
 * @return QMItems item on success, NULL on fail
 */
QMItems* QM_Create(OpCont* _ops, SubCont* _subs, const char* _path);
/** 
 * @brief This function deals with user requests, it operates as a thread
 * @param[in] _qm - structure that holdes aggregators
 * @return NULL
 */
void* QM_Operate(void* _qm);

#endif /* __QM_H__ */


