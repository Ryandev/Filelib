/**
 @file
 Read/Write from/to files
 
 @author Ryan Powell
 @date 03-10-11
 @copyright
     Copyright (c) 2011  Ryan Powell \n
     Proprietary & Confidential \n
     This file & associated documentation may not be used without the consent of the authors permission. \n
     Undocumented use of this material is an infringement of copyright. \n
 */


#include <string.h>
#include "FileLib.h"
#include "FileLib_common.h"
#include "FileLib_util.h"


typedef struct _FILE_HANDLE_STRUCT
{
    uint32_t bufferSize;
    uint8_t * buffer;
    FILE * file;
} FILE_HANDLE_STRUCT;


bool file_doesFileExist ( char * fileName, uint32_t fileNameLen )
{
    bool doesFileExist = false;
    
    if ( ( fileName == NULL ) || ( fileNameLen == 0U ) )
    {
        FILEPRINT_DBG_E("NULL handle passed to %s:%d",__FUNCTION__,__LINE__);
    }
    else
    {
        FILE * file = fopen(fileName, "r");

        if (file)
        {
            fclose(file);        
            doesFileExist = true;
        }
    }

    return doesFileExist;    
}

bool file_deleteFile ( char * fileName, uint32_t fileNameLen )
{
    bool wasDeleted = false;
    
    if ( ( fileName == NULL ) || ( fileNameLen == 0U ) )
    {
        FILEPRINT_DBG_E("NULL handle passed to %s:%d",__FUNCTION__,__LINE__);
    }
    else
    {
        int status = remove(fileName);

        if ( status == 0 )
        {
            wasDeleted = true;
        }
    }

    return wasDeleted;
}

FILE_STATUS file_openFile ( char * fileName, uint32_t fileNameLen, FILE_HANDLE * handle )
{
    FILE_STATUS status = FILE_STATUS_UNDEF;
    
    if ( ( fileName == NULL ) || ( fileNameLen == 0U ) || ( handle == NULL ) )
    {
        status = FILE_STATUS_FAIL_NULL_HANDLE;
    }
    else if ( file_doesFileExist(fileName, fileNameLen) == false )
    {
        status = FILE_STATUS_FAIL_FILE_DOES_NOT_EXIST;
    }
    else
    {
        FILE * file = openFile(fileName, fileNameLen);
        
        if ( file )
        {
            FILE_HANDLE_STRUCT *handlePrv = file_memAlloc(sizeof(FILE_HANDLE_STRUCT));
            
            if ( handlePrv )
            {
                memset(handlePrv,'\0',sizeof(FILE_HANDLE_STRUCT));
                
                handlePrv->file = file;
                
                *handle = handlePrv;
                
                status = FILE_STATUS_OK;
            }
            else
            {
                closeFile(file);
                FILEPRINT_DBG_E("Malloc failure %s:%d",__FUNCTION__,__LINE__);
                status = FILE_STATUS_FAIL_MALLOC_ERROR;
            }
        }
        else
        {
            status = FILE_STATUS_FAIL_FILE_DOES_NOT_EXIST;
        }
    }
    
    return status;
}

FILE_STATUS file_closeFile ( FILE_HANDLE handle )
{
    FILE_STATUS status = FILE_STATUS_UNDEF;
    
    if ( handle == NULL )
    {
        status = FILE_STATUS_FAIL_NULL_HANDLE;
    }
    else
    {
        FILE_HANDLE_STRUCT * handlePrv = (FILE_HANDLE_STRUCT *)handle;
        
        closeFile(handlePrv->file);
        
        file_memFree(handlePrv->buffer);
        
        file_memFree(handlePrv);
        
        status = FILE_STATUS_OK;
    }
    
    return status;
}

FILE_STATUS file_getContents ( FILE_HANDLE handle, uint8_t ** buffer, uint32_t * bufferSize )
{
    FILE_STATUS status = FILE_STATUS_UNDEF;
    
    if ( ( handle == NULL ) || ( buffer == NULL ) || ( bufferSize == NULL ) )
    {
        status = FILE_STATUS_FAIL_NULL_HANDLE;
    }
    else
    {
        FILE_HANDLE_STRUCT * handlePrv = (FILE_HANDLE_STRUCT *)handle;
        
        if ( handlePrv->buffer == NULL )
        {
            /* havent retrieved the file from memory yet */
            handlePrv->bufferSize = fileSize(handlePrv->file);
            handlePrv->buffer = readFileToBuffer(handlePrv->file);
        }

        *buffer = handlePrv->buffer;
        *bufferSize = handlePrv->bufferSize;
        
        status = FILE_STATUS_OK;
    }
    
    return status;
}

FILE_STATUS file_saveContentsFromBufferToFile ( uint8_t * buffer, uint32_t bufferSize, char * fileName, uint32_t fileNameLen )
{
    FILE_STATUS status = FILE_STATUS_UNDEF;
    
    if ( ( fileName == NULL ) || ( fileNameLen == 0U ) || ( buffer == NULL ) || ( bufferSize == 0U ) )
    {
        status = FILE_STATUS_FAIL_NULL_HANDLE;
    }
    else
    {
        FILE * file = createFile(fileName, fileNameLen);
        
        if ( file )
        {
            writeBufferToFile(buffer, bufferSize, file);
            closeFile(file);

            status = FILE_STATUS_OK;
        }
        else
        {
            status = FILE_STATUS_FAIL_FILE_DOES_NOT_EXIST;
        }
    }
    
    return status;
}


FILE_STATUS file_baseName ( char * filename, char * baseFileName, uint8_t baseFileNameSize )
{
    FILE_STATUS status = FILE_STATUS_UNDEF;
    uint8_t offsetForLocalPathOnly = 0U;
    uint8_t index = 0U;
    
    if ( (filename) && (baseFileName) && (baseFileNameSize!=0) )
    {
        while ( filename[index] != '\0' )
        {
            if ( filename[index] == FILESYSTEM_DIRECTORY_SEPERATOR )
            {
                offsetForLocalPathOnly = index;
            }
            
            index++;
        }
        
        /* +1 to ignore the / prefix */
        snprintf((char *)baseFileName, baseFileNameSize, "%s",(char*)&filename[offsetForLocalPathOnly+1]);
        
        status = FILE_STATUS_OK;
    }
    else
    {
        status = FILE_STATUS_FAIL_NULL_HANDLE;
    }
    
    return status;
}

