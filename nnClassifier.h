#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void nnClassifier(matrix *Xtr, matrix *Ytr, matrix *Xte, matrix *Yte)
{   
    int correct = 0;
    matrix inter = create(Xte->rows, Xtr->rows);
    
    for(int i = 0; i < Xte->rows; i++)
        for(int j = 0; j < Xtr->rows; j++)
            for(int k = 0; k < Xtr->cols; k++)
                inter.vals[i][j] += abs(Xte->vals[i][k] - Xtr->vals[j][k]);
    
    float *Ypred = min(&inter, 1);
    delete(inter);

    for(int i = 0; i < Xte->rows; i++)
        Ypred[i] = Ytr->vals[(int)Ypred[i]][0];
    
    for(int i = 0; i < Xte->rows; i++)
        if((int)Ypred[i] == (int)Yte->vals[i][0])
                ++correct;
    
    float accuracy = (correct)*0.01;
    printf("\n Accuracy : %f", accuracy);

    free(Ypred);       
}

#endif