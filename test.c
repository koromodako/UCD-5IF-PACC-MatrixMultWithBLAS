/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   test.c
Author: koromodako
Date:   2016-10-05
Purpose:
    Contains function implementations related to matrix tests.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
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
int sqmat_cmp(double **A, double **B, int n)
{
    int ret, i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            if (A[i][j]!=B[i][j]) {
                ret=1;
                goto end;
            }
        }
    }
    ret=0;
end:
    return ret;
}
/*-----------------------------------------------------------------------------
sqmat_fill
    Fill the matrix using the following function f(i,j)=min(i,j)
M [in]
    Square matrix to fill
n [in]
    Size of the square matrix
-----------------------------------------------------------------------------*/
void sqmat_fill(double **M, int n)
{
    int i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            M[i][j]=(i<j?i:j); 
        }
    }
}
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
void sqmat_fill_const(double **M, int n, double val)
{
    int i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            M[i][j]=val; 
        }
    }
}
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
void sqmat_fill_mult(double **M, int n)
{
    int i, j, k;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            for (k=0; k<n; ++k) {
                M[i][j]+=(k<i?k:i)*(k<j?k:j);     
            }
        }
    }   
}
/* macro to execute a secure matrix allocation */
#define MAT_ALLOC(Mat, Mode, Val)                           \
    if(sqmat_alloc(&Mat, MAT_SIZE, Mode, Val)!=SUCCESS) {   \
        goto end;                                           \
    }
/* macro to print a matrix with a header */
#define MAT_PRINT(Header, Mat)   \
    printf(Header);              \
    sqmat_print(Mat, MAT_SIZE);
/* macro to test matrix multiplication */
#define TEST_MAT_MULT(Header, func)     \
    printf(Header);                     \
    func(A, A, R, MAT_SIZE);            \
    if (sqmat_cmp(R, T, MAT_SIZE)!=0) { \
        ret=E_FAIL;                     \
        PRINT_ERR(ret);                 \
        goto end;                       \
    }                                   \
    MAT_PRINT("---------------- result matrix ----------------\n", R)
/* macro to test block matrix multiplication */
#define TEST_MAT_MULT_BLOCK(Header, func)   \
    printf(Header);                         \
    func(A, A, R, MAT_SIZE, BLOCK_SIZE);    \
    if (sqmat_cmp(R, T, MAT_SIZE)!=0) {     \
        ret=E_FAIL;                         \
        PRINT_ERR(ret);                     \
        goto end;                           \
    }                                       \
    MAT_PRINT("---------------- result matrix ----------------\n", R)
/*---------------------------------------------------------------------------
test_mult_functions
    Execute a test to check if multiplication functions return a true result
---------------------------------------------------------------------------*/
int test_mult_functions(void)
{
    int ret;
    double **T=NULL, **A=NULL, **R=NULL;
    /* display introduction message */
    printf("==================== TEST ====================\n");
    /* alloc target matrix: expected result of sqmat_fill*sqmat_fill */
    MAT_ALLOC(T, InitRand, 0.0)
    /* alloc simple matrix */
    MAT_ALLOC(A, InitRand, 0.0)
    /* alloc result matrix */
    MAT_ALLOC(R, InitZero, 0.0)
    /* fill target matrix */
    sqmat_fill_mult(T, MAT_SIZE);
    /* fill simple matrix */
    sqmat_fill(A, MAT_SIZE);
    /* display target matrix */
    MAT_PRINT("---------------- target matrix ----------------\n", T)
    /* display simple matrix */
    MAT_PRINT("---------------- simple matrix ----------------\n", A)
    /* display result matrix */
    MAT_PRINT("---------------- result matrix ----------------\n", R)
    /* compute multilication */
    TEST_MAT_MULT("Computing R=A*A using sqmat_mult_ijk...\n", sqmat_mult_ijk)
    /* compute multilication */
    sqmat_fill_const(R, MAT_SIZE, 0.0);
    TEST_MAT_MULT_BLOCK("Computing R=A*A using sqmat_mult_ijk_block...\n",
                  sqmat_mult_ijk_block)
    /* compute multilication */
    sqmat_fill_const(R, MAT_SIZE, 0.0);
    TEST_MAT_MULT_BLOCK("Computing R=A*A using sqmat_mult_kij_block...\n",
                  sqmat_mult_kij_block)
    /* compute multilication */
#ifdef USE_BLAS
    sqmat_fill_const(R, MAT_SIZE, 0.0);
    TEST_MAT_MULT("Computing R=A*A using sqmat_mult_blas...\n", 
        sqmat_mult_blas)
#endif /* USE_BLAS */
    ret=SUCCESS;
end:
    sqmat_free(R);
    sqmat_free(A);
    sqmat_free(T);
    return ret;
}

#undef TEST_MAT_MULT_BLOCK
#undef TEST_MAT_MULT
#undef MAT_PRINT
#undef MAT_ALLOC