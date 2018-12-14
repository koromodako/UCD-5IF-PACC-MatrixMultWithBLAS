/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   matrix.h
Author: koromodako
Date:   2016-10-05
Purpose:
    This file defines all functions prototypes needed to manipulate matrices
    from alloc to free. 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "error.h"

#define MAT_SIZE    12
#define BLOCK_SIZE  4
/*=============================================================================
                            Allocation/Free
=============================================================================*/
/*-----------------------------------------------------------------------------
InitMode
    Enumeration of the modes used to initialize matrix's values
-----------------------------------------------------------------------------*/
typedef enum _InitMode {
    InitZero,
    InitConst,
    InitRand
} InitMode;
/*-----------------------------------------------------------------------------
sqmat_alloc
    Allocate memory to store (row-wise) a square matrix of size m    
M [out]
    Matrix
Mm [out]
    Matrix memory zone
n [in]
    Size of the matrix
mode [in]
    Initialization mode for matrix values
init [in]
    Initial value of all the matrix
-----------------------------------------------------------------------------*/
int sqmat_alloc(double ***M, int n, InitMode mode, double init);
/*-----------------------------------------------------------------------------
sqmat_free
    Free memory used to store
M [in]
    Matrix
Mm [in]
    Matrix memory zone
-----------------------------------------------------------------------------*/
void sqmat_free(double **M);
/*=============================================================================
                                    Debug
=============================================================================*/
/*-----------------------------------------------------------------------------
sqmat_print
    Print the content of a matrix
A [in]
    Matrix to print
n [in]
    Size of the matrix
-----------------------------------------------------------------------------*/
int sqmat_print(double **A, int n);
/*=============================================================================
                                Multiplication
=============================================================================*/
/*-----------------------------------------------------------------------------
sqmat_mult_ijk
    ijk straight-forward algorithm computing A*B=C. A, B and C must be the 
    same size n.
A [in]
    First operand of the multiplication
B [in]
    Second operand of the multiplication
C [in/out]
    Matrix resulting of the multiplication, must be allocated before the 
    function is called.
n [in]
    Size of the matrices
-----------------------------------------------------------------------------*/
int sqmat_mult_ijk(double **A, double **B, double **C, int n);
/*-----------------------------------------------------------------------------
sqmat_mult_ijk_block

A [in]
    First operand of the multiplication
B [in]
    Second operand of the multiplication
C [in/out]
    Matrix resulting of the multiplication, must be allocated before the 
    function is called.
n [in]
    Size of the matrices
-----------------------------------------------------------------------------*/
int sqmat_mult_ijk_block(double **A, double **B, double **C, int n, 
    int b);
/*-----------------------------------------------------------------------------
sqmat_mult_kij_block

A [in]
    First operand of the multiplication
B [in]
    Second operand of the multiplication
C [in/out]
    Matrix resulting of the multiplication, must be allocated before the 
    function is called.
n [in]
    Size of the matrices
-----------------------------------------------------------------------------*/
int sqmat_mult_kij_block(double **A, double **B, double **C, int n, 
    int b);
/*-----------------------------------------------------------------------------
sqmat_mult_blas

A [in]

B [in]

C [in/out]

n [in]

int [ret]
    Always return SUCCESS
-----------------------------------------------------------------------------*/
#ifdef USE_BLAS
int sqmat_mult_blas(double **A, double **B, double **C, int n);
#endif /* USE_BLAS */
/*=============================================================================
                                    Tests
=============================================================================*/
/*-----------------------------------------------------------------------------
sqmat_cmp
    Compare two square matrices to see if they are equal
A [in]
    First square matrix to compare
B [in]
    Second square matrix to compare
n [in]
    Size of the square matrix
int [ret]
    0 if matrices are equal,
    1 if matrices are not equal
-----------------------------------------------------------------------------*/
int sqmat_cmp(double **A, double **B, int n);
/*-----------------------------------------------------------------------------
sqmat_fill
    Fill the matrix using the following function f(i,j)=min(i,j)
M [in]
    Square matrix to fill
n [in]
    Size of the square matrix
-----------------------------------------------------------------------------*/
void sqmat_fill(double **M, int n);
/*-----------------------------------------------------------------------------
sqmat_fill_const
    Fill the given matrix with a constant value
M [in]
    Square matrix to fill
n [in]
    Size of the square matrix
val [in]
    Constant value to put in each cell of the matrix
void [ret]    
-----------------------------------------------------------------------------*/
void sqmat_fill_const(double **M, int n, double val);
/*-----------------------------------------------------------------------------
sqmat_fill_mult
    Fill the matrix using the value returned by 
    f(i,j,k)=sum[k=0..n](min(i,k)*min(k,j))
M [in]
    Square matrix to initialize
n [in]
    Size of the square matrix
void [ret]
-----------------------------------------------------------------------------*/
void sqmat_fill_mult(double **M, int n);
/*---------------------------------------------------------------------------
test_mult_functions
    Execute a test to check if multiplication functions return a true result
---------------------------------------------------------------------------*/
int test_mult_functions(void);

#endif /*_MATRIX_H_*/