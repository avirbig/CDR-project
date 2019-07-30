/** 
 *  @file subss_container.h
 *  @brief Generic Container of cellular data of Inter-subscriber communication
 *			Date Created: 19.02.2019
 * 
 *  @author Avishai Cohen
 * 
 *  @bug No known bugs! 
 */

#include <stdlib.h>		/* malloc */
#include <stdio.h>		/* printf */

#include "fw.h"
#include "sHashMap.h"
#include "sub.h"
#include "subs_container.h"
#include "macros.h"

#define NUM_OF_MUTEXES 10

struct SubCont{
	HashMap* m_map;
};

/*************************************************************************************/
						/* FUNCS FOR CONTAINER */
/*************************************************************************************/
static Ulong SubCont_Hash(const void* _key)
{
	Ulong res;
	
	res = *(Ulong*)_key;
	
	return res;
}

static int SubCont_IsEqual(const void* _key1, const void* _key2)
{
	return (*(Ulong*) _key1) == (*(Ulong*) _key2);
}

static int SubCont_PrintAllKeys(const void* _key, void* _value, void* _context)
{
	printf("KEY: %ld\n", *(Ulong*)_key);
	
	Sub_PrintValues((Sub*)_value);
	
	return 1;
}

static int SubCont_PrintAllKeysToFile(const void* _key, void* _value, void* _context)
{
	Sub* sub = _value;
	char subData[STR_SIZE]; 
	FILE* fd = _context;
	
	Sub_GetData(sub, subData);
	
	FW_WriteSingleLine(subData, fd);
	
	return 1;
}
/*************************************************************************************/
							/* PRIMARY FUNCTIONS */
/*************************************************************************************/
SubCont* SubCont_Create(size_t _numOfSubscribers)
{
	SubCont* subs = NULL;
	
	subs = malloc(sizeof(SubCont));
	if(!IS_VALID(subs))
	{
		return NULL;
	}
	
	subs->m_map = HashMapCreate(_numOfSubscribers, SubCont_Hash, SubCont_IsEqual, NUM_OF_MUTEXES);
	if(!IS_VALID(subs->m_map))
	{
		free(subs);
		return NULL;
	}
	
	return subs;
}
/*************************************************************************************/
void SubCont_Destroy(SubCont* _subs)
{
	if(!IS_VALID(_subs))
	{
		return;
	}
	
	HashMapDestroy(&_subs->m_map, NULL, Sub_Destroy);
	free(_subs);
}
/*************************************************************************************/
static SubCont_Result SubCont_Insert(SubCont* _subs, Ulong _key, Cdr* _c)
{
	Sub* sub = NULL;
	SubCont_Result res = SUBCONT_SUCCESS;
	
	sub = Sub_Create(_key);
	if(!sub)
	{
		STDERR_PRINT("sub_Create Fail\n");
		return SUBCONT_ALLOCATION_ERROR;
	}
	
	Sub_Update(sub, _c);
	res = HashMapInsert(_subs->m_map, Sub_GetIdAddres(sub), sub);
	if(!IS_EQUAL(res, SUBCONT_SUCCESS))
	{
		STDERR_PRINT("sub HashMapInsert Fail\n");
		Sub_Destroy(sub);
	}
	
	return res;
}
/*************************************************************************************/
SubCont_Result SubCont_Update(SubCont* _subs,Cdr* _c)
{
	Ulong key;
	SubCont_Result res = SUBCONT_SUCCESS;
	
	if(!IS_VALID(_subs) || !IS_VALID(_c))
	{
		return SUBCONT_UNINITIALIZED_ERROR;
	}
	
	key = Cdr_GetIMSI(_c);
	
	res = HashMapFindUpdate(_subs->m_map, &key, Sub_Update, _c);
	if(!IS_EQUAL(res, SUBCONT_SUCCESS))
	{
		res = SubCont_Insert(_subs, key, _c);
	}
	
	return res;
}
/*************************************************************************************/
SubCont_Result SubCont_GetSubscriberData(SubCont* _subs, Ulong _subId, char* _line)
{
	if(!IS_VALID(_subs) || !IS_VALID(_line))
	{
		return SUBCONT_UNINITIALIZED_ERROR;
	}
	
	return HashMapFindUpdate(_subs->m_map, &_subId, Sub_GetData, _line);
}
/*****************************************************************************/
					/* PRINTING / DEBUG FUNCS */
/*****************************************************************************/
Ulong SubCont_PrintAll(SubCont* _subs)
{
	if(!IS_VALID(_subs))
	{
		return -1;
	}

	return HashMapForEach(_subs->m_map, SubCont_PrintAllKeys, NULL);
}
/*****************************************************************************/
void SubCont_PrintAllToFile(SubCont* _subs, const char* _path)
{
	FILE* fd = NULL;
	
	if(!IS_VALID(_subs))
	{
		return;
	}
	
	fd = File_WOpen(_path);
	
	FW_WriteHeader(fd);
	
	FW_WriteSingleLine("ALL SUBSCRIBERS REPORT:\n\n", fd);

	HashMapForEach(_subs->m_map, SubCont_PrintAllKeysToFile, fd);

	File_WClose(fd);
}






