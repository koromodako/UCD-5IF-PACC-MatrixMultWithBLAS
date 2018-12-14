/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   error.c
Author: koromodako
Date:   2016-10-05
Purpose:
    This file contains the implementation of functions related to error 
    handling.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "error.h"
#include <stdio.h>
/* macro used to print errors */
#define PRINT_ERROR(func, msg) \
    printf("[ERR](%s): %s\n", func, msg);
/*----------------------------------------------------------------------------
print_error
    Display an error
func [in]
    Function name
err [in]
    Code of the error to display
----------------------------------------------------------------------------*/
void print_error(const char *func, int err)
{
    switch (err) {
        case SUCCESS:
            PRINT_ERROR(func, "no error.");
            break;
        case E_INVALID_ARG:
            PRINT_ERROR(func, "invalid argument!");
            break;
        case E_NO_MEM:
            PRINT_ERROR(func, "out of memory!");
            break;
        case E_FAIL:
            PRINT_ERROR(func, "fail!");
            break;
        default:
            PRINT_ERROR(func, "/!\\ unhandled error /!\\")
            break;
    }
}