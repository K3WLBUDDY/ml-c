#ifndef SVM_H
#define SVM_H

#define RANDMAX 255

#include "matrix.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

matrix weights;
matrix loss;
matrix hypothesis;
double totalLoss = 0.00;

void hingeLoss(matrix Xtr, matrix Ytr)
{
    float hyperParameter = 1.0;
    //double totalLoss = 0.00;
    double tempLoss = 0.00;

    for(int i = 0; i < Xtr.rows; i++)
    {
        printf("\n Iteration : %d", i);
        for(int j = 0; j < 10; j++)
        {
            if(j == (int)Ytr.vals[i][0])
                continue;
            else
                for(int k =0; k < weights.cols; k++)
                {
                    tempLoss +=  weights.vals[j][k]*Xtr.vals[i][k] - weights.vals[(int)Ytr.vals[i][0]][k] *Xtr.vals[i][k];
                }
        }
        tempLoss += hyperParameter;
        if(tempLoss < 0)
        {   printf("\n LUL WOT");
            tempLoss = 0;
        }
        totalLoss +=tempLoss;
    }

    totalLoss = totalLoss * 0.00002;

    printf("\n Weird total Loss : %lf", totalLoss);
}

void svm_init(matrix Xtr, matrix Ytr)
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

   //matrix model = dot(&weights, &Xtr);

    /*
    matrix hypo[50000];
    for(int i = 0; i < Xtr.rows; i++)
    {
        matrix temp = create(3073, 1);
        for(int j =0 ;j < Xtr.cols; j++) 
            temp.vals[i][0] = Xtr.vals[i][j];
        
        hypo[i] = dot(&weights, &temp);
        

    }
    */
    

    //delete(weights);

    hingeLoss(Xtr, Ytr);

    
    
}




#endif