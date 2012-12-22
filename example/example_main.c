

#include <stdio.h>
#include <string.h>
#include "Filelib.h"


#define fileexample "/tmp/example.test"
#define message "hello world"


int main(int argc, const char * argv[])
{
    
    file_deleteFile(fileexample,strlen(fileexample));

    file_saveContentsFromBufferToFile ( (uint8_t*)message, strlen(message), fileexample, strlen(fileexample) );
    
    FILE_HANDLE fHandle = FILE_HANDLE_INVALID;
    
    file_openFile ( fileexample, strlen(fileexample), &fHandle );
    
    char *fBuffer = NULL;
    uint32_t fSize = 0U;
    
    file_getContents ( fHandle, (uint8_t**)&fBuffer, &fSize );
    
    printf("Got contents: %.11s\n",fBuffer);

    file_deleteFile(fileexample,strlen(fileexample));

    return 0;
}

