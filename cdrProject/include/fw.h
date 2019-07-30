/**
 *  Author :			Avishai Cohen
 *  Creation date :     19.02.19
 *  Date last modified :
 * 						
 *  Description : 		file writing API for cdr report
 **/
#ifndef __FW_H__
#define __FW_H__
/** 
 * @brief This program opens file to read CDR lines from it
 * 
 * @param[in] _path - full path to file including name
 * @returns file handler on success, NULL on fail
 */
FILE* File_WOpen(const char* _path);
/** 
 * @brief This program closes file opened by File_Open
 * 
 * @param[in] _fd - pointer to file
 * @returns 0 on success, EOF on Fail
 */
int File_WClose(FILE* _fd);
/** 
 * @brief This program reads line, and send it via channel
 * 
 * @param[in] _fd - file descriptor
 * @param[in] _line - char pointer to line
 * @returns non-negative num on success, EOF on fail
 */
int FW_WriteSingleLine(const char* _line, FILE* _fd);
/** 
 * @brief This program purpose is to write header to report file
 * @description header consist of date and time in format: YYYY/MM/DD. HH:MM:SS
 * 
 * @param[in] _fd - file descriptor
 * @returns non-negative num on success, EOF on fail
 */
int FW_WriteHeader(FILE* _fd);

#endif /* __FW_H__ */
