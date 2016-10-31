/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   mult.c
Author: paul dautry
Date:   2016-10-05
Purpose:
    This file contains the implementation of multiplication operations listed 
    in matrix.h 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "matrix.h"
#include "error.h"
#ifdef USE_BLAS
#   include <cblas.h>
#endif
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
    function is called
n [in]
    Size of the matrices
int [ret]
    0 if success,
    error code if failed
int [ret]
    Always return SUCCESS
-----------------------------------------------------------------------------*/
int sqmat_mult_ijk(double **A, double **B, double **C, int n)
{
    int i, j, k;
    double sum;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            sum = 0;
            for (k=0; k<n; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }    
    }
    return SUCCESS;
}
/*-----------------------------------------------------------------------------
sqmat_mult_ijk_block
    Perform a matrix multiplication iterating over blocks
A [in]
    First operand of the multiplication
B [in]
    Second operand of the multiplication
C [in/out]
    Matrix resulting of the multiplication, must be allocated before the 
    function is called. 
    /!\ Must be filled with zeros
n [in]
    Size of the matrices
int [ret]
    Always return SUCCESS
-----------------------------------------------------------------------------*/
int sqmat_mult_ijk_block(double **A, double **B, double **C, int n, int b)
{
    int i, j, k, p, q, r, sum;
    /* iterate over matrices */
    for (i=0; i<n/b; ++i) {
        for (j=0; j<n/b; ++j) {
            for (k=0; k<n/b; ++k) {
                /* iterate over blocks */
                for (p=0; p<b; ++p) {
                    for (q=0; q<b; ++q) {
                        sum = 0;
                        for (r=0; r<b; ++r) {
                            sum += A[i*b+p][k*b+r] * B[k*b+r][j*b+q];
                        }
                        C[i*b+p][j*b+q] += sum; 
                    }
                }
            }
        }    
    }
    return SUCCESS;
}
/*-----------------------------------------------------------------------------
sqmat_mult_kij_block
    Perform a matrix multiplication iterating over blocks
A [in]
    First operand of the multiplication
B [in]
    Second operand of the multiplication
C [in/out]
    Matrix resulting of the multiplication, must be allocated before the 
    function is called.
    /!\ Must be filled with zeros
n [in]
    Size of the matrices
int [ret]
    Always return SUCCESS
-----------------------------------------------------------------------------*/
int sqmat_mult_kij_block(double **A, double **B, double **C, int n, int b)
{
    int i, j, k, p, q, r, x;
    /* iterate over matrices */
    for (k=0; k<n/b; ++k) {
        for (j=0; j<n/b; ++j) {
            for (i=0; i<n/b; ++i) {
                /* iterate over blocks */    
                for (r=0; r<b; ++r) {
                    for (p=0; p<b; ++p) {
                        x = A[i*b+p][k*b+r];
                        for (q=0; q<b; ++q) {
                            C[i*b+p][j*b+q] += x * B[k*b+r][j*b+q];
                        }
                    }
                }
            }
        }    
    }
    return SUCCESS;
}
/*-----------------------------------------------------------------------------
sqmat_mult_blas
    Perform a matrix multiplication iterating over blocks
A [in]
    First operand of the multiplication
B [in]
    Second operand of the multiplication
C [in/out]
    Matrix resulting of the multiplication, must be allocated before the 
    function is called
n [in]
    Size of the matrices
int [ret]
    Always return SUCCESS
-----------------------------------------------------------------------------*/
#ifdef USE_BLAS
int sqmat_mult_blas(double **A, double **B, double **C, int n)
{
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 
        1., A[0], n, B[0], n, 1., C[0], n);
    return SUCCESS;
}
#endif /* USE_BLAS */
