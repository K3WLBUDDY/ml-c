#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include <stdio.h>
#include "matrix.h"
//Include the header file that contains the function to be used
matrix numericalGradientDescent(float (*lossFunction)(matrix, matrix), matrix Xtr, matrix Ytr, matrix weights, float h=0.0001)
{
    float loss = lossFunction(Xtr, Ytr);
    float temp;
    float fxh;
    matrix gradient = create(weights.rows, weights.cols);

    for(int i = 0; i < weights.rows; i++)
        for(int j = 0; j < weights.cols; j++)
        {
            temp = weights.vals[i][j];
            weights.vals[i][j] += h;
            fxh = lossFunction(Xtr, Ytr);
            weights.vals[i][j] = temp;
            gradient.vals[i][j] = (fxh - loss)*(1/h);
        }
    return gradient;
}


matrix analyticalGradientDescent(float (*lossFunction)(matrix, matrix), matrix Xtr, matrix Ytr, matrix weights)
{
    matrix gradient = create(weights.rows, weights.cols);
    for(int i = 0; i < weights.rows; i++)
        for(int j = 0; j < weights.cols; j++)
        {
            float tempLoss = lossFunction(Xtr, Ytr);

            if(tempLoss > 0)
            {
                if 
                gradient.vals[i][j] = 
        }
}

matrix gradientCheck(float (*lossFunction)(matrix, matrix), matrix Xtr, matrix Ytr)
{

}
#endif