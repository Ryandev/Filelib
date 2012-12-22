/**
 @file
 Read/Write from/to files
 
 @author Ryan Powell
 @date 22-12-12
 @copyright Copyright (c) 2012  Ryan Powell 
 @licence https://raw.github.com/mcCuppaT/Filelib/master/LICENSE
 */


#ifndef _FILELIB_H
#define _FILELIB_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>


#ifdef _WIN32
    #define FILESYSTEM_DIRECTORY_SEPERATOR '\'
#else
    #define FILESYSTEM_DIRECTORY_SEPERATOR '/'
#endif


typedef void* FILE_HANDLE;

/** value to indicate #FILE_HANDLE is invalid */
#define FILE_HANDLE_INVALID NULL


/**
 @enum _FILE_STATUS
 @brief return codes from FileLib api's \n
 #FILE_STATUS_OK success \n
 FILE_STATUS_FAIL_NULL_HANDLE NULL handle passed to api \n
 FILE_STATUS_FAIL_FILE_DOES_NOT_EXIST invalid file name passed \n
 FILE_STATUS_FAIL_MALLOC_ERROR internal failure - unable to alloc memory \n
 FILE_STATUS_FAIL function call failed \n
 */
typedef enum _FILE_STATUS
{
    FILE_STATUS_UNDEF,
    FILE_STATUS_OK,
    FILE_STATUS_FAIL_NULL_HANDLE,
    FILE_STATUS_FAIL_FILE_DOES_NOT_EXIST,
    FILE_STATUS_FAIL_MALLOC_ERROR,
    FILE_STATUS_FAIL,
    FILE_STATUS_LAST_VALUE,
} FILE_STATUS;


/**
 @brief test whether file exists
 @param[in] fileName name of file
 @param[in] fileNameLen number of characters in fileName
 @return returns #TRUE if file exists
 */
bool file_doesFileExist ( char * fileName, uint32_t fileNameLen );


/**
 @brief if file exists delete
 @param[in] fileName name of file
 @param[in] fileNameLen number of characters in fileName
 @return returns #TRUE if file was deleted
 */
bool file_deleteFile ( char * fileName, uint32_t fileNameLen );

/**
 @brief open file & return handle
 @param[in] fileName name of file
 @param[in] fileNameLen number of characters in fileName
 @param[out] handle returned handle ( only valid if call succeeds )
 @return returns #FILE_STATUS_OK on success
*/
FILE_STATUS file_openFile ( char * fileName, uint32_t fileNameLen, FILE_HANDLE * handle );


/**
 @brief close file handle
 @details this does not save the changed contents
 @param[in] handle file handle to close ( must have been opened with file_openFile
 @return returns #FILE_STATUS_OK on success
 */
FILE_STATUS file_closeFile ( FILE_HANDLE handle );


/**
 @brief get the contents of the file
 @details returned buffer is owned by the filelib. Copy first before editing
 @param[in] handle file handle to close
 @param[out] buffer returned file contents
 @param[out] bufferSize number of bytes in buffer
 @return returns #FILE_STATUS_OK on success
 */
FILE_STATUS file_getContents ( FILE_HANDLE handle, uint8_t ** buffer, uint32_t * bufferSize );


/**
 @brief from a given buffer write to file
 @details if file already exists overwrite
 @param[in] buffer buffer contents to save
 @param[in] bufferSize size of buffer
 @param[in] fileName name of file to write to
 @param[in] fileNameLen length of fileName in bytes
 @return returns #FILE_STATUS_OK on success
 */
FILE_STATUS file_saveContentsFromBufferToFile ( uint8_t * buffer, uint32_t bufferSize, char * fileName, uint32_t fileNameLen );


/**
 @brief from a given filepath return the basename.
 @details I.e if filename = "/home/user/fileA" basename = fileA
 @param[in] filename NULL terminated string of which basename to retrive from
 @param[out] baseFileName string to write basename to
 @param[in] baseFileNameSize maximum number of characters to write to param-baseFileName
 @return returns #FILE_STATUS_OK on success
 */
FILE_STATUS file_baseName ( char * filename, char * baseFileName, uint8_t baseFileNameSize );


#define FILELIB_VERSION 1.0f

    
#ifdef __cplusplus
}
#endif


#endif /* _FILELIB_H */
