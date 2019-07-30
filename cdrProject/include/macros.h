#include <stdio.h> 	/* printf */

#ifndef __MACROS_H__
#define __MACROS_H__
/** 
 * @brief Useful macros, used freaquently in other modules
 * 
 * @author Avishai Cohen
 */ 

/* TYPEDEF */

typedef unsigned long Ulong;
/***********************************************************************/

/* ARITHMATIC CALCS */

#define MICRO_IN_MILLI 1000
#define MILLI_TO_MICRO(X) (X) * MICRO_IN_MILLI
/***********************************************************************/
/* BOOLEAN */

#ifndef FALSE
	#define FALSE 0
#endif  /* FALSE */

#define TRUE 1
/***********************************************************************/
/* VALIDATION */

#ifndef MAGIC_OK
	#define MAGIC_OK 0xbeafbeaf
#endif  /* MAGIC_OK */

#define IS_VALID(X) ((X) != NULL)
#define IS_NOT_VALID(X) !IS_VALID(X)
#define IS_MAGIC_VALID(X) (MAGIC_OK == (X)->m_magicNumber)
#define IS_EQUAL(X,Y) ((X) == (Y))
/***********************************************************************/

/* STDERR */

#define STDERR_IS_EQUAL_STATUS(VAR, VAL,STR) if((VAR) == (VAL)) fprintf(stderr,STR);
#define STDERR_NOT_EQUAL_STATUS(VAR, VAL,STR) if((VAR) != (VAL)) fprintf(stderr,STR);
#define STDERR_PRINT(STR) fprintf(stderr,(STR))
/***********************************************************************/

/* PRINT */

#define PRINT_ARR(NUM, START_INDX ,ARR) 		\
	do{	int i;									\
		for(i = (START_INDX); i <= (NUM); ++i)	\
		printf("%d=%d ",i,(ARR)[i] ); 			\
		printf("\n");	}						\
	while(0)

/***********************************************************************/

/* STRING MANIPULATION */

#ifndef STR_SIZE
	#define STR_SIZE 300
#endif  /* STR_SIZE */

#define MAX_FILE_NAME 100


#define STR(a) #a

#define FULLPATH(TEMP,DIR,F_NAME) 	\
	do{								\
		strcpy(TEMP,DIR);			\
		strcat(TEMP,F_NAME);} 		\
	while(0)

/***********************************************************************/

/* CHANNELS AND MESSAGES */

#define CHANNEL_DEFAULT_INT 1
#define CHANNEL_QM_INT 2

#define CHANNEL_DEFAULT_TYPE 1
#define CHANNEL_ALL_TYPES 0

#define  MSG_SIZE sizeof(Msg_Buffer) - sizeof(long)

#define DISPATCHER_PATH "/home/avishai/work/ipc/cdrProject/dispatcher/dispatch.c"
#define UI_PATH "/home/avishai/work/ipc/cdrProject/ui"
#define FILE_MONITOR_PATH "/home/avishai/work/ipc/cdrProject/newfm/newfm.c"
/***********************************************************************/

/* USER INTERFACE */

#define IS_OPTION_VALID(X) ((X) >= 0) && ((X) < 8)
#define IS_OPTION_INVALID(X) ((X) < 0) || ((X) > 8)
/***********************************************************************/

/* SEMAPHORES */

#define SEMAPHORE_NAME "/newfm.c"
#define SEMAPHORE_PERMISSIONS 0664

#endif /* __MACROS_H__ */
