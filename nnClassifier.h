#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void predict(matrix *Xtr, matrix *Ytr, matrix *Xte, matrix *Yte)
{   
    int correct = 0;
    matrix inter = create(Xte->rows, Xtr->rows);
    
    for(int i = 0; i < Xte->rows; i++)
    {   
        printf("\n Iteration %d", i);
        for(int j = 0; j < Xtr->rows; j++)
            for(int k = 0; k < Xtr->cols; k++)
                inter.vals[i][j] += abs(Xte->vals[i][k] - Xtr->vals[j][k]);
    }
 
    
    float *Ypred = min(&inter, 1);

    delete(inter);

    for(int i = 0; i < Xte->rows; i++)
        Ypred[i] = Ytr->vals[(int)Ypred[i]][0];

    for(int i = 0; i < Xte->rows; i++)
        printf("\n Scores : %d", (int)Ypred[i]);

    
    
    for(int i = 0; i < Xte->rows; i++)
        if((int)Ypred[i] == (int)Yte->vals[i][0])
            {
                ++correct;
                printf(" \n Correct Label %d", i);
            }
    
    float accuracy = (correct)*0.01;
    printf("\n No. of Correct Values : %d", correct);
    printf("\n Accuracy : %f", accuracy);

    free(Ypred);
    
        
}

void test(matrix Xte, matrix Yte)
{

}

#endif