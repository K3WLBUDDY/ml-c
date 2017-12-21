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
matrix gradient;
double totalLoss = 0.00;

float hingeLoss(matrix Xtr, matrix Ytr)
{
    float hyperParameter = 1.0;
    totalLoss = 0.00;
    double tempLoss = 0.00;

    for(int i = 0; i < Xtr.rows; i++)
    {
        //printf("\n Iteration : %d", i);
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
        {   //printf("\n LUL WOT");
            tempLoss = 0;
        }
        totalLoss +=tempLoss;
    }

    totalLoss = totalLoss * 0.00002;

    printf("\n Weird total Loss : %lf", totalLoss);
    return tempLoss;
}

void svm_init(matrix Xtr, matrix Ytr)
{
    weights = create(10, 3073);
    matrix newWeights = create(10, 3072);
    loss = create(50000, 1);
    hypothesis = create(50000, 10);
    gradient = create(10, 3073);
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

    float temp = hingeLoss(Xtr, Ytr);
    float h = 0.01;
    int count = 0;
    //while(totalLoss > 2)
   // {
        //printf("\n Count : %d", count);
        for(int i = 0; i < weights.rows; i++)
        {
            printf("\n Row : %d",i);
            for(int j = 0; j < weights.cols; j++)
            {
                printf("\n Iteration : %d",j );
                float oldValue = weights.vals[i][j];
                weights.vals[i][j] += oldValue + h;
                float currLoss = hingeLoss(Xtr, Ytr);
                weights.vals[i][j] = oldValue;
                gradient.vals[i][j] = currLoss - temp / h;
            }
        }
            //count++
    //}

    //matrix newWeights = create(10, 3072);
    matrix test = scale(gradient, -6);
    newWeights = sub(weights,test);
    float newLoss = hingeLoss(Xtr, Ytr);

    printf("\n New Loss : %f", newLoss);

    
    
}




#endif