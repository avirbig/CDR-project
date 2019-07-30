/** 
 *  @file ops_container.h
 *  @brief Generic Container of cellular operator data of Inter-Operator communication
 *			Date Created: 12.02.2019
 * 
 *  @author Avishai Cohen
 * 
 *  @bug No known bugs! 
 */


#ifndef __OPS_CONTAINER_H__
#define __OPS_CONTAINER_H__

#include <stddef.h>  /* size_t */
#include "cdr.h" /* Cdr */

typedef struct OpCont OpCont;

typedef enum OpCont_Result{
	OPCONT_SUCCESS = 0,
	OPCONT_UNINITIALIZED_ERROR, 		/**< Uninitialized OPCONT error 	*/
	OPCONT_KEY_NULL_ERROR, 				/**< Key was null 					*/
	OPCONT_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 			*/
	OPCONT_KEY_NOT_FOUND_ERROR, 		/**< Key not found 					*/
	OPCONT_ALLOCATION_ERROR, 			/**< Allocation error 	 			*/
	OPCONT_INVALID_INPUT_ERROR,
	OPCONT_VALUE_NULL_ERROR
}OpCont_Result;

typedef enum Operators_Id{
	CELLCOM = 42502,
	PELEPHONE = 42503,
	ORANGE = 42504
}Operators_Id;

/*************************************************************************************/
							/* PRIMARY FUNCTIONS */
/*************************************************************************************/
/** 
 * @brief Create a new Container of cellular operator data of Inter-Operator communication
 * @param[in] _numOfOperators - num of other operators
 * @param[in] _myOpID - id of specific operator
 * @return newly created Operator Container or null on failure
 */
OpCont* OpCont_Create(size_t _numOfOperators, size_t _myOpID);
/** 
 * @brief Updates Data stored in Operator container according to Cdr
 * @param[in] _ops - pointer to perator container
 * @param[in] _c - Incoming Single Cdr
 * @return OPCONT_SUCCESS - on successfull update
 * 			OPCONT_KEY_NOT_FOUND_ERROR - if Cdr containes Id of unkown operator
 */
OpCont_Result OpCont_Update(OpCont* _ops, Cdr* _c);
/** 
 * @brief Get single operator data as a string format
 * @param[in] _ops - pointer to perator container
 * @param[in] _opId - id of specific operator
 * @param[out] _line - pointer to buffer to store data into
 * @return OPCONT_SUCCESS - on successfull attempt
 * 			OPCONT_KEY_NOT_FOUND_ERROR - if id of operator not found
 * 			OPCONT_UNINITIALIZED_ERROR
 */
OpCont_Result OpCont_GetOperatorData(OpCont* _ops, size_t _opId, char* _line);
/** 
 * @brief Destroys Operator Container and Deallocates all data allocated for this purpose
 * @param[in] _ops - pointer to perator container
 * @return void
 */
void OpCont_Destroy(OpCont* _ops);

/*****************************************************************************/
					/* PRINTING / DEBUG FUNCS */
/*****************************************************************************/
/** 
 * @brief Prints Data of all Operators stored in container
 * @param[in] _ops - pointer to perator container
 * @return int - num of operators this function has printed, -1 on Fail
 */
size_t OpCont_PrintAll(OpCont* _ops);
/** 
 * @brief Prints Data of all Subscribers stored in container to file
 * @param[in] _ops - pointer to perator container
 * @param[in] _path - path + name of file
 * @return void
 * @warning Report does not erases previous data
 */
void OpCont_PrintAllToFile(OpCont* _ops, const char* _path);

#endif /* __OPS_CONTAINER_H__ */
