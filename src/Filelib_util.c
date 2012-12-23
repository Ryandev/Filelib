/**
 @file
 Filelib - utility calls
 
 @author Ryan Powell
 @date 22-12-12
 @copyright Copyright (c) 2012  Ryan Powell 
 @licence https://raw.github.com/Ryandev/Filelib/master/LICENSE
 */


#include "FileLib_util.h"
#include "FileLib_common.h"


FILE * createFile( char * file, uint32_t fileLen )
{
    FILE * fileHandle = NULL;
    
    if ( ( file != NULL ) && ( fileLen != 0U ) )
    {
        fileHandle = fopen(file, "a+");
    }
    else
    {
        FILEPRINT_DBG_E("Null handle to %s:%d",__FUNCTION__,__LINE__);
    }
    
    return fileHandle;
}

FILE * openFile( char * file , uint32_t fileLen )
{
    FILE * fileHandle = NULL;
    
    if ( ( file != NULL ) && ( fileLen != 0U ) )
    {
        fileHandle = fopen(file, "r");
    }
    else
    {
        FILEPRINT_DBG_E("Null handle to %s:%d",__FUNCTION__,__LINE__);
    }

    return fileHandle;
}

void closeFile ( FILE * file )
{
    if ( file )
    {
        fclose(file);
    }
    else
    {
        FILEPRINT_DBG_E("Null handle to %s:%d",__FUNCTION__,__LINE__);
    }
}

uint32_t fileSize ( FILE * file )
{
    uint32_t size = 0U;
    
    if ( file )
    {
        fseek(file , 0 , SEEK_END);
        size = (uint32_t)ftell(file);
        rewind(file);    
    }
    else
    {
        FILEPRINT_DBG_E("Null handle to %s:%d",__FUNCTION__,__LINE__);
    }

    return size;
}

uint8_t* readFileToBuffer ( FILE * file )
{
    uint8_t * buffer = NULL;
    
    if ( file )
    {
        uint32_t fileLen = fileSize(file);
        
        FILEPRINT_ASSERT(fileLen!=0U);
        
        buffer = file_memAlloc( fileLen * sizeof(uint8_t) );

        if ( buffer )
        {
            uint32_t bytesRead = (uint32_t)fread(buffer, 1, fileLen, file);

            if ( bytesRead != fileLen )
            {
                FILEPRINT_DBG_E("Warning whole buffer not read %u!=%u",bytesRead,fileLen);
            }
        }
        else
        {
            FILEPRINT_DBG_E("Malloc failure: %s:%d",__FUNCTION__,__LINE__);
        }
    }
    else
    {
        FILEPRINT_DBG_E("Null handle to %s:%d",__FUNCTION__,__LINE__);
    }
    
    FILEPRINT_DBG_I("Returning buffer: %p\n",buffer);
 
    return buffer;
}

void writeBufferToFile ( uint8_t * buffer, uint32_t bufferSize, FILE * file )
{
    if ( ( buffer != NULL ) && ( bufferSize != 0U ) && ( file != NULL ) )
    {
        uint32_t bytesWritten = (uint32_t)fwrite(buffer, (size_t)1, (size_t)bufferSize, file);
        
        if ( bytesWritten != bufferSize )
        {
            FILEPRINT_DBG_E("Warning whole buffer not written %u!=%u",bytesWritten,bufferSize);
        }
    }
    else
    {
        FILEPRINT_DBG_E("Null handle to %s:%d",__FUNCTION__,__LINE__);
    }
}