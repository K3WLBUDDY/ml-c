#ifndef SVM_H
#define SVM_H

#define RANDMAX 255

#include "matrix.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
matrix weights;

void svm_init(matrix Xtr, matrix Ytr)
{
    weights = create(10, 3073);
    for(int i = 0 ; i < weights.rows; i++)
        weights.vals[i][(weights.cols) - 1] = 1.0;

    srand(time(NULL));

    for(int i = 0; i < weights.rows; i++)
        for(int j = 0; j < weights.cols - 1; j++)
                weights.vals[i][j] = 0.01 * (rand() % RANDMAX);
                
    Xtr = reshape(Xtr, Xtr.rows, Xtr.cols+1);

    for(int i = 0; i < Xtr.rows; i++)
            Xtr.vals[i][Xtr.cols - 1] = 1.0;

    delete(weights);

    hingeLoss(Xtr, Ytr);
    
}

void hingeLoss(matrix Xtr, matrix Ytr)
{

}


#endif