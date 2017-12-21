#ifndef SOFTMAX_H
#define SOFTMAX_H

#include "matrix.h"
#include <time.h>

matrix weights;
matrix loss;
matrix hypothesis;

void softmax_init(matrix Xtr, matrix Ytr)
{
    weights = create(10, 3073);
    loss = create(50000, 1);
    hypothesis = create(50000, 10);

    for(int i = 0 ; i < weights.rows; i++)
        weights.vals[i][(weights.cols) - 1] = 1.0;

    srand(time(NULL));

    for(int i = 0; i < weights.rows; i++)
        for(int j = 0; j < weights.cols - 1; j++)
                weights.vals[i][j] = 0.01 * (rand() % 2);
                
    Xtr = reshape(Xtr, Xtr.rows, Xtr.cols+1);

    for(int i = 0; i < Xtr.rows; i++)
            Xtr.vals[i][Xtr.cols - 1] = 1.0;
}

float crossEntropyLoss(matrix Xtr, matrix Ytr)
{
    
}

#endif
