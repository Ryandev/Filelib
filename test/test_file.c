

#include "test_file.h"
#include "FileLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define FILELIB_TEST_FILE "/tmp/testfile.abc"


bool test_file_nullParam ( void )
{
    bool didPass = false;
    void * ptr = (void*)1;
    
    if ( file_doesFileExist(NULL, 10) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_openFile(NULL, 100, ptr) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_openFile(ptr, 100, NULL) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_closeFile(NULL) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_getContents(NULL, ptr, ptr) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_getContents(ptr, NULL, ptr) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_getContents(ptr, ptr, NULL) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_saveContentsFromBufferToFile(NULL, 1, ptr, 1) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_saveContentsFromBufferToFile(ptr, 1, NULL, 1) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_baseName(NULL, (void*)100, 1) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_baseName((void*)100, NULL, 1) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else if ( file_baseName((void*)100, (void*)100, 0) == FILE_STATUS_OK )
    {
        printf("NULL param failed: %s:%d\n",__FUNCTION__,__LINE__);
    }
    else
    {
        didPass = true;
    }
    
    return didPass;
}

bool test_file_doesFileExist ( void )
{
    bool didPass = false;
    FILE_HANDLE handle = NULL;
    uint32_t bufferSize = 32U;
    uint8_t * buffer = malloc(sizeof(uint8_t)*bufferSize);
    
    for ( uint32_t i=0U; i<bufferSize; i++ )
    {
        buffer[i] = (uint8_t)i;
    }
    
    /* remove the file if it exists before starting the test */
    if ( file_doesFileExist(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE)) )
    {
        file_deleteFile(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE));
    }
    
    /* test start */
    if ( file_doesFileExist(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE)) )
    {
        printf("File should not exist!\n");
    }
    else if ( file_openFile(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE), &handle) == FILE_STATUS_OK )
    {
        printf("opened non-existant file\n");
    }
    else if ( file_saveContentsFromBufferToFile(buffer, bufferSize, FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE)) != FILE_STATUS_OK )
    {
        printf("Failed to write to file\n");
    }
    else if ( file_doesFileExist(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE)) == false )
    {
        printf("New file does not exist\n");
    }
    else
    {
        didPass = true;
    }
    
    free(buffer);
    
    return didPass;
}

bool test_file_readWrite ( void )
{
    bool didPass = false;
    FILE_HANDLE handle = NULL;
    uint32_t bufferSize = 32U;
    uint8_t * buffer = malloc(sizeof(uint8_t)*bufferSize);
    
    for ( uint32_t i=0U; i<bufferSize; i++ )
    {
        buffer[i] = (uint8_t)i;
    }
    
    uint8_t * bufferLoaded = NULL;
    uint32_t bufferLoadedSize = 0U;
    
    /* remove the file if it exists before starting the test */
    if ( file_doesFileExist(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE)) )
    {
        file_deleteFile(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE));
    }
    
    /* test start */
    if ( file_saveContentsFromBufferToFile(buffer, bufferSize, FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE)) != FILE_STATUS_OK )
    {
        printf("Failed to save file\n");
    }
    else if ( file_openFile(FILELIB_TEST_FILE, sizeof(FILELIB_TEST_FILE), &handle) != FILE_STATUS_OK )
    {
        printf("Failed to open file\n");
    }
    else if ( file_getContents(handle, &bufferLoaded, &bufferLoadedSize) != FILE_STATUS_OK )
    {
        printf("Failed to get file contents\n");
    }
    else
    {
        if ( bufferSize != bufferLoadedSize )
        {
            printf("buffer size mismatch %d!=%d\n",bufferSize,bufferLoadedSize);
        }
        else if ( bufferLoaded == NULL )
        {
            printf("No buffer loaded\n");
        }
        else
        {
            didPass = true;

            for ( uint32_t i=0U; i<bufferSize; i++ )
            {
                if ( buffer[i] != bufferLoaded[i] )
                {
                    didPass = false;
                    printf("buffer loaded mismatch (%d) %u!=%u\n",i,buffer[i],bufferLoaded[i]);
                }
            }
            
        }
    }
    
    return didPass;
}

bool test_file_baseName()
{
    bool didPass = false;
    
    char testname[32];

    snprintf(testname, 32, "%c%s%c%s%c%s",FILESYSTEM_DIRECTORY_SEPERATOR,"pathA",FILESYSTEM_DIRECTORY_SEPERATOR,"pathB",FILESYSTEM_DIRECTORY_SEPERATOR,"pathC");
    
    char *basenameExpected = "pathC";
    
    char basename[32];
    
    if ( file_baseName(testname, basename, 32) != FILE_STATUS_OK )
    {
        printf("file_baseName return failed\n");
    }
    else if ( strcmp(basename,basenameExpected) == 0 )
    {
        didPass = true;
    }
    else
    {
        printf("basename mismatch. Got:%s Expected:%s\n",basename,basenameExpected);
    }
    
    return didPass;
}

bool test_file ( void )
{
    bool b_nullParam = test_file_nullParam();
    bool b_doesFileExist = test_file_doesFileExist();
    bool b_readWrite = test_file_readWrite();
    bool b_baseName = test_file_baseName();
    
    if ( b_nullParam && b_doesFileExist && b_readWrite && b_baseName )
    {
        return true;
    }
    
    return false;
}