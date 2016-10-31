/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   main.c
Author: paul dautry
Date:   2016-10-05
Purpose:
    Matmult program entry point.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "time_macro.h"
#include "matrix.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_N 256
#define DFLT_N 32
#define DFLT_B 8
#define TIME_FORMAT "%.5f"

/*  */
int benchmark_mult_functions(int n, int b);
/*  */
int main(int argc, char **argv) 
{
    int n, b, ret;
    if (MAT_SIZE%BLOCK_SIZE!=0) {
        ret=E_INVALID_ARG;
        PRINT_ERR(ret);
        goto end;
    }
    if (argc<2) {
        test_mult_functions();
        printf("==================== TIME ====================\n");
        benchmark_mult_functions(DFLT_N, DFLT_B);
    } else {
        if (!strcmp(argv[1], "test")) {
            test_mult_functions();
        } else if (!strcmp(argv[1], "time")) {
            for (n=4; n<=MAX_N; n+=2) {
                for (b=2; b<=n/2; b+=2) {
                    if (n%b==0) {
                        printf("==================== TIME ====================\n");
                        benchmark_mult_functions(n, b);        
                    }
                }
            }
        } else {
            ret=E_UNEXPECTED;
            PRINT_ERR(ret);
            goto end;
        }    
    }
    ret=SUCCESS;
end:
    return ret;
}
/*  */
int benchmark_mult_functions(int n, int b)
{
    /* variables */
    int ret;
    double **A=NULL, **B=NULL, **R=NULL;
    DECL_TIMEIT_VARS();
    /* function logic */
    printf("parameters (n=%d, b=%d)\nresults:\n", n, b);
    /* test n = a*b */
    if (n%b!=0) {
        ret=E_INVALID_ARG;
        PRINT_ERR(ret);
        goto end;
    }
    /* matrices alloc */
    if ((ret=sqmat_alloc(&A, n, InitRand, 0.0))!=SUCCESS) {
        goto end;
    }
    if ((ret=sqmat_alloc(&B, n, InitRand, 0.0))!=SUCCESS) {
        goto end;
    }
    if ((ret=sqmat_alloc(&R, n, InitZero, 0.0))!=SUCCESS) {
        goto end;
    }
    /* init matrices */
    sqmat_fill(A, n);
    sqmat_fill(B, n);
    /* benchmark ijk */
    TIMEIT("sqmat_mult_ijk: "TIME_FORMAT"\n", ret, 
        sqmat_mult_ijk, A, B, R, n);
    sqmat_fill_const(A, n, 0.0);
    /* benchmark ijk blocked */
    TIMEIT("sqmat_mult_ijk_block: "TIME_FORMAT"\n", ret, 
        sqmat_mult_ijk_block, A, B, R, n, b);
    sqmat_fill_const(B, n, 0.0);
    /* benchmark kij blocked */
    TIMEIT("sqmat_mult_kij_block: "TIME_FORMAT"\n", ret, 
        sqmat_mult_kij_block, A, B, R, n, b);
    sqmat_fill_const(A, n, 0.0);
    /* benchmark blas */
#ifdef USE_BLAS
    TIMEIT("sqmat_mult_blas: "TIME_FORMAT"\n", ret, 
        sqmat_mult_blas, A, B, R, n);
#endif /* USE_BLAS */
    /* success */
    ret=SUCCESS;
end:
    sqmat_free(R);
    sqmat_free(B);
    sqmat_free(A);
    return ret;
}