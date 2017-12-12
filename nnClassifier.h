#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include "matrix.h"
#include <math.h>
#include <stdlib.h>

void predict(matrix *Xtr, matrix *Ytr, matrix *Xte, matrix *Yte)
{   

    float *trainTotal = (float *)calloc(Xtr->rows, sizeof(float *));
    float *testTotal = (float *)calloc(Xte->rows, sizeof(float *));
    float *minValues = (float *)calloc(Xte->rows, sizeof(float*));
    matrix scores = create(Xte->rows, Xtr->rows);
    float *Ypred = calloc(Xte->rows, sizeof(float *));
    
    for(int i = 0; i < Xtr->rows; i++)
        for(int j = 0; j < Xtr->cols; j++)
        {    
            trainTotal[i] += Xtr->vals[i][j];
            if(i < Xte->rows)
                testTotal[i] += Xte->vals[i][j];
        }

    for(int i = 0; i < Xte->rows; i++)
        for(int j = 0; j < Xtr->rows; j++)
            scores.vals[i][j] = abs(testTotal[i] - trainTotal[j]);

    Ypred = min(&scores, 1);

    for(int i = 0; i < Xte->rows; i++)
        Ypred[i] = Ytr->vals[(int)Ypred[i]][0];

    for(int i = 0; i < Xte->rows; i++)
        printf("\n Scores : %d", (int)Ypred[i]);

    delete(scores);
    free(testTotal);
    free(trainTotal);

    int correct = 0;
        printf("\n Size of Stuff : %d", Yte->rows);
    for(int i = 0; i < Xte->rows; i++)
        if((int)Ypred[i] == (int)Yte->vals[i][0])
            ++correct;
    
    float accuracy = (correct)*0.01;
    printf("\n No. of Correct Values : %d", correct);
    printf("\n Accuracy : %f", accuracy);
        
}

void test(matrix Xte, matrix Yte)
{

}

#endif