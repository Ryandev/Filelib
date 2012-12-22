/**
 @file
 Filelib - common definitions
 
 @author Ryan Powell
 @date 03-10-11
 @copyright
     Copyright (c) 2011  Ryan Powell \n
     Proprietary & Confidential \n
     This file & associated documentation may not be used without the consent of the authors permission. \n
     Undocumented use of this material is an infringement of copyright. \n
 */


#ifndef _FILELIB_COMMON_H
#define _FILELIB_COMMON_H


#ifdef __cplusplus
extern "C" {
#endif


/* Enable to trace any defects in DebugPrint */
/* #define FILE_PRINT_DEBUG */

#include <stdio.h>

#ifdef FILE_PRINT_DEBUG
    #define FILEPRINT_DBG(level,format, ... ) \
    do \
    { \
        fprintf (stdout,"FileLib %s (%s:%d): ",level,__FUNCTION__,__LINE__); \
        fprintf (stdout, format, ##__VA_ARGS__ ); \
        fprintf (stdout, "\n"); \
    } while (0)

    #define FILEPRINT_DBG_E(fmt, ... ) FILEPRINT_DBG("-ERROR-",fmt, ##__VA_ARGS__)
    #define FILEPRINT_DBG_I(fmt, ... ) FILEPRINT_DBG("-INFO-",fmt, ##__VA_ARGS__)
    #define FILEPRINT_ASSERT(cond) \
        if ( (cond) != TRUE ) \
        { \
            FILEPRINT_DBG_E("Assertion failure (%s:%d)",__FILE__,__LINE__); \
        }

#else
    #define FILEPRINT_DBG_E(fmt, ...) {}
    #define FILEPRINT_DBG_I(fmt, ...) {}
    #define FILEPRINT_ASSERT(cond) {}
#endif
    
    
#ifdef __cplusplus
}
#endif


#endif /* _FILELIB_COMMON_H */