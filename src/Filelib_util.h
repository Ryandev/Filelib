/**
 @file
 Filelib - utility calls
 
 @author Ryan Powell
 @date 22-12-12
 @copyright Copyright (c) 2012  Ryan Powell 
 @licence https://raw.github.com/Ryandev/Filelib/master/LICENSE
 */


#ifndef _FILELIB_UTIL_H
#define _FILELIB_UTIL_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define file_memAlloc malloc
#define file_memFree free


/**
 @brief open file and get #FILE handle
 @param[in] file name of file including full path
 @param[in] fileLen length of param file
 @return returns non-NULL on success
 */
FILE * openFile( char * file , uint32_t fileLen );


/**
 @brief create empty file & return handle
 @param[in] file filename
 @param[in] fileLen length of above param
 @return returns non-NULL on success
 */
FILE * createFile( char * file, uint32_t fileLen );


/**
 @brief from a given handle, close
 @param[in] file file handle to close
 */
void closeFile ( FILE * file );


/**
 @brief return number of bytes in file
 @param[in] file file handle
 @return returns byte size of file
 */
uint32_t fileSize ( FILE * file );


/**
 @brief from a given file write to buffer
 @details returned pointer must be freed. To get file size of buffer call #fileSize
 @return returns non-NULL on success
 */
uint8_t* readFileToBuffer ( FILE * file );


/**
 @brief write buffer contents to file
 @param[in] buffer save contents
 @param[in] bufferSize size of buffer
 @param[in] file file handle to write to
 */
void writeBufferToFile ( uint8_t * buffer, uint32_t bufferSize, FILE * file );
    
    
#ifdef __cplusplus
}
#endif


#endif /* _FILELIB_UTIL_H */
