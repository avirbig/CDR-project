/** 
 *  @file subss_container.h
 *  @brief Generic Container of cellular data of Inter-subscriber communication
 *			Date Created: 19.02.2019
 * 
 *  @author Avishai Cohen
 * 
 *  @bug No known bugs! 
 */


#ifndef __SUBS_CONTAINER_H__
#define __SUBS_CONTAINER_H__

#include <stddef.h>  /* size_t */
#include "cdr.h" /* Cdr */

typedef struct SubCont SubCont;


typedef enum SubCont_Result{
	SUBCONT_SUCCESS = 0,
	SUBCONT_UNINITIALIZED_ERROR, 		/**< Uninitialized SUBCONT error 	*/
	SUBCONT_KEY_NULL_ERROR, 				/**< Key was null 					*/
	SUBCONT_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 			*/
	SUBCONT_KEY_NOT_FOUND_ERROR, 		/**< Key not found 					*/
	SUBCONT_ALLOCATION_ERROR, 			/**< Allocation error 	 			*/
	SUBCONT_INVALID_INPUT_ERROR,
	SUBCONT_VALUE_NULL_ERROR
}SubCont_Result;

/*************************************************************************************/
							/* PRIMARY FUNCTIONS */
/*************************************************************************************/
/** 
 * @brief Create a new Container of cellular subscriber data of Inter-Subscriber communication
 * @param[in] _numOfSubscribers - initial num of total subscribers
 * @return newly created Subscriber Container or null on failure
 */
SubCont* SubCont_Create(size_t _numOfSubscribers);
/** 
 * @brief Updates Data stored in Subscriber container according to Cdr
 * @param[in] _subs - pointer to perator container
 * @param[in] _c - Incoming Single Cdr
 * @return OPCONT_SUCCESS - on successfull update
 * 			OPCONT_KEY_NOT_FOUND_ERROR - if Cdr containes Id of unkown subscriber
 */
SubCont_Result SubCont_Update(SubCont* _subs, Cdr* _c);
/** 
 * @brief Get single subscriber data as a string format
 * @param[in] _subs - pointer to perator container
 * @param[in] _subId - id of specific subscriber
 * @param[out] _line - pointer to buffer to store data into
 * @return OPCONT_SUCCESS - on successfull attempt
 * 			OPCONT_KEY_NOT_FOUND_ERROR - if id of subscriber not found
 * 			OPCONT_UNINITIALIZED_ERROR
 */
SubCont_Result SubCont_GetSubscriberData(SubCont* _subs, Ulong _subId, char* _line);
/** 
 * @brief Destroys Subscriber Container and Deallocates all data allocated for this purpose
 * @param[in] _subs - pointer to subscriber container
 * @return void
 */
void SubCont_Destroy(SubCont* _subs);

/*****************************************************************************/
					/* PRINTING / DEBUG FUNCS */
/*****************************************************************************/
/** 
 * @brief Prints Data of all Subscribers stored in container
 * @param[in] _subs - pointer to perator container
 * @return int - num of subscribers this function has printed, -1 on Fail
 */
size_t SubCont_PrintAll(SubCont* _subs);
/** 
 * @brief Prints Data of all Subscribers stored in container to file
 * @param[in] _subs - pointer to perator container
 * @param[in] _path - path + name of file
 * @return void
 * @warning Report does not erases previous data
 */
void SubCont_PrintAllToFile(SubCont* _subs, const char* _path);

#endif /* __SUBS_CONTAINER_H__ */
