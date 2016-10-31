/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   error.h
Author: paul dautry
Date:   2016-10-05
Purpose:
    This file defines all error codes used within the program and function prototypes for error-related operations 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _ERROR_H_
#define _ERROR_H_
/* success codes */
#define SUCCESS         0
/* error codes */
#define E_INVALID_ARG   10
#define E_NO_MEM        11
#define E_FAIL          12
#define E_UNEXPECTED    13
/*----------------------------------------------------------------------------
print_error
    Display an error
func [in]
    Function name
err [in]
    Code of the error to display
----------------------------------------------------------------------------*/
void print_error(const char *func, int err);
/* macro used to print errors */
#define PRINT_ERR(err) \
    print_error(__FUNCTION__, err)

#endif /*_ERROR_H_*/