/**
 *  Author :			Avishai Cohen
 *  Creation date :     14.02.2019
 *  Date last modified :
 * 						
 *  Description : 		file monitoring API by Polling Method
 * 						This Program uses posix semaphores to limit
 * 						Max number of concurrently running file readers
 **/
#ifndef __FM_H__
#define __FM_H__

#include <stdio.h> /* FILE */

/** 
 * @brief This program opens file to read CDR lines from it
 * 
 * @param[in] _path - full path to file including name
 * @returns file handler on success, NULL on fail
 */
FILE* File_Open(const char* _path);
/** 
 * @brief This program closes file opened by File_Open
 * 
 * @param[in] _fd - pointer to file
 * @returns 0 on success, EOF on Fail
 */
int File_Close(FILE* _fd);
/** 
 * @brief moves file from working dir to finished dir
 * 
 * @param[in] _oldpath
 * @param[in] _newpath
 * @returns 0 SUCCESS, -1 FAIL 
 */
int File_Move(const char* _oldpath, const char* _newpath);
/** 
 * @brief scan files in directory, execute program that read lines and sends them to channel
 * 			moves the files to other directory
 * @param[in] _execPath - path to executable file
 * @param[in] _ipath - initial directory path
 * @param[in] _wpath - working (In Progress) directory path
 * @param[in] _fpath - final (done) directory path
 * @param[in] _maxRunning - max num of concurrently running file readers
 * @returns 0 SUCCESS, -1 FAIL 
 */
int File_ScanExecMove(const char* _execPath, const char* _ipath, const char* _wpath, const char* _fpath, int _maxRunning);

#endif /* #ifndef __FM_H__ */
