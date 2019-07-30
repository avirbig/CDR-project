#include <stdlib.h>		/* malloc */
#include <stdio.h>		/* printf */

#include "fw.h"
#include "sHashMap.h"
#include "operator.h"
#include "ops_container.h"
#include "macros.h"

#define NUM_OF_MUTEXES 1


struct OpCont{
	size_t m_myOpId;
	HashMap* m_map;
};

char* Ops_Names[] = {"Cellcom","Pelephone", "Orange"};

const size_t Ops_Id[] = {42502, 42503, 42504};

/*************************************************************************************/
						/* FUNCS FOR CONTAINER */
/*************************************************************************************/
static size_t OpCont_Hash(const void* _key)
{
	size_t res;
	
	res = *(size_t*)_key % 10;
	
	return res;
}

static int OpCont_IsEqual(const void* _key1, const void* _key2)
{
	return (*(size_t*) _key1) == (*(size_t*) _key2);
}

static int OpCont_PrintAllKeys(const void* _key, void* _value, void* _context)
{
	printf("KEY: %ld\n", *(size_t*)_key);
	
	Op_PrintValues((Op*)_value);
	
	return 1;
}

static int OpCont_PrintAllKeysToFile(const void* _key, void* _value, void* _context)
{
	Op* op = _value;
	char opData[STR_SIZE]; 
	FILE* fd = _context;
	
	Op_GetData(op, opData);
	
	FW_WriteSingleLine(opData, fd);
	
	return 1;
}
/*************************************************************************************/
							/* PRIMARY FUNCTIONS */
/*************************************************************************************/
static OpCont_Result OpCont_OperatorsInit(OpCont* _ops ,size_t _numOfOperators, size_t _myOpID)
{
	int i = 0, insertRes;
	Op* tempOp = NULL;
	
	for(i = 0; i < _numOfOperators + 1; ++i) /* +1 -> our operator which isn't created */
	{
		if(IS_EQUAL(Ops_Id[i], _myOpID))
		{
			continue;
		}
		
		tempOp = Op_Create(Ops_Id[i], Ops_Names[i]);
		if(!IS_VALID(tempOp))
		{
			Op_Destroy(tempOp);
			return OPCONT_ALLOCATION_ERROR;
		}
		
		insertRes = HashMapInsert(_ops->m_map, &Ops_Id[i], tempOp);
		printf("insertRes = %d. i = %d\n", insertRes, i);
		if(!IS_EQUAL(insertRes, MAP_SUCCESS))
		{
			return OPCONT_ALLOCATION_ERROR;
		}
	}
	
	return OPCONT_SUCCESS;
}
/*************************************************************************************/
OpCont* OpCont_Create(size_t _numOfOperators, size_t _myOpID)
{
	OpCont* ops = NULL;
	int res = 0;
	
	ops = malloc(sizeof(OpCont));
	if(!IS_VALID(ops))
	{
		return NULL;
	}
	
	ops->m_map = HashMapCreate(_numOfOperators, OpCont_Hash, OpCont_IsEqual, NUM_OF_MUTEXES);
	if(!IS_VALID(ops->m_map))
	{
		free(ops);
		return NULL;
	}
	
	res = OpCont_OperatorsInit(ops, _numOfOperators, _myOpID);
	if(!IS_EQUAL(res, OPCONT_SUCCESS))
	{
		OpCont_Destroy(ops);
		return NULL;
	}
	
	ops->m_myOpId = _myOpID;
	
	return ops;
}
/*************************************************************************************/
void OpCont_Destroy(OpCont* _ops)
{
	if(!IS_VALID(_ops))
	{
		return;
	}
	
	HashMapDestroy(&_ops->m_map, NULL, Op_Destroy);
	free(_ops);
}
/*************************************************************************************/
OpCont_Result OpCont_Update(OpCont* _ops,Cdr* _c)
{
	OpCont_Result res = OPCONT_SUCCESS;
	MapResult mRes = MAP_SUCCESS;
	int key = Cdr_GetOpId(_c);
	
	if(!IS_VALID(_ops) || !IS_VALID(_c))
	{
		return OPCONT_UNINITIALIZED_ERROR;
	}
	
	mRes = HashMapFindUpdate(_ops->m_map, &key, Op_Update, _c);
	if(MAP_SUCCESS != mRes)
	{
		return mRes;
	}
	
	return res;
}
/*************************************************************************************/
OpCont_Result OpCont_GetOperatorData(OpCont* _ops, size_t _opId, char* _line)
{
	OpCont_Result res = OPCONT_SUCCESS;
	MapResult mRes = MAP_SUCCESS;
	
	if(!IS_VALID(_ops) || !IS_VALID(_line))
	{
		return OPCONT_UNINITIALIZED_ERROR;
	}
	
	mRes = HashMapFindUpdate(_ops->m_map, &_opId, Op_GetData, _line);
	if(MAP_SUCCESS != mRes)
	{
		return mRes;
	}
	
	return res;
}
/*****************************************************************************/
					/* PRINTING / DEBUG FUNCS */
/*****************************************************************************/
size_t OpCont_PrintAll(OpCont* _ops)
{
	if(!IS_VALID(_ops))
	{
		return -1;
	}

	return HashMapForEach(_ops->m_map, OpCont_PrintAllKeys, NULL);
}
/*****************************************************************************/
void OpCont_PrintAllToFile(OpCont* _ops, const char* _path)
{
	FILE* fd = NULL;
	
	if(!IS_VALID(_ops))
	{
		return;
	}
	
	fd = File_WOpen(_path);
	
	FW_WriteHeader(fd);
	
	FW_WriteSingleLine("ALL OPERATORS REPORT:\n\n", fd);
	
	HashMapForEach(_ops->m_map, OpCont_PrintAllKeysToFile, fd);
	
	File_WClose(fd);
}








