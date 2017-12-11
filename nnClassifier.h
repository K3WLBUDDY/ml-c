#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include "matrix.h"
#include "stdlib.h"

matrix predict(matrix *Xtr, matrix *Ytr, matrix *Xte)
{   

    float *trainTotal = (float *)calloc(Xtr->rows, sizeof(float));
    float *testTotal = (float *)calloc(Xte->rows, sizeof(float));
    matrix scores = create(Xte->rows, Xte->cols);

    for(int i = 0; i < Xtr->rows; i++)
        for(int j = 0; j < Xtr->cols; j++)
        {    
            trainTotal[i] += Xtr->vals[i][j];
            if(i < 10000)
                testTotal[i] += Xte->vals[i][j];
        }

    for(int i = 0; i < Xte->rows; i++)
        for(int j = 0; j < Xtr->rows; j++)
            scores.vals[i][j] = testTotal[i] - trainTotal[j];

        
}

void test(matrix Xte, matrix Yte)
{

}

#endif