

#include <stdio.h>
#include "test_file.h"


int main(int argc, const char * argv[])
{
    int status = test_file() ? 0 : 1;
    fprintf(stdout, "File Test: %s\n", ( status ? "failed" : "passed" ) );
    return status;
}

