#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix
{
    long int rows, cols;
    float **vals;
}matrix;

matrix create(int rows, int cols)
{
    matrix m;
    m.rows = rows;
    m.cols = cols;
    m.vals = calloc(m.rows, sizeof(float *));

    for(int i = 0; i < m.rows; i++)
            m.vals[i] = calloc(m.cols, sizeof(float));
    
    return m;
}

void shape(matrix m)
{
    printf("\n (%d, %d)", m.rows, m.cols);
}


void delete(matrix m)
{
    for(int i = 0; i < m.rows; i++)
        free(m.vals[i]);
    free(m.vals);
}


void print(matrix m)
{
    for(int i = 0; i < m.rows; i++)
    {   
         printf("\n");
         for(int j = 0; j < m.cols; j++)
            printf(" | %f", m.vals[i][j]);
    }
    printf("\n");
    
}

matrix scale(matrix m, float scale)
{
    matrix s = create(m.rows, m.cols);
    for(int i = 0; i < m.rows; i++)
        for(int j = 0; j < m.cols; j++)
            s.vals[i][j] = m.vals[i][j] * scale;
    
    return s;
}

void loadFromCSV(char *filePath)
{
    //TODO
}

matrix dot(matrix *m1, matrix *m2)
{   
    matrix m3 = create(m1->rows, m2->cols);

    if(m1->cols != m2->rows)
        printf("\n Incompatible shapes");

    else 
        for(int i = 0; i < m1->rows; i++)
            for(int j = 0; j < m2->cols; j++)
                for(int k = 0; k < m1->rows; k++)
                    m3.vals[i][j] += m1->vals[i][k] * m2->vals[k][j];

    return m3;
}

matrix reshape(matrix m, int rows, int cols)
{
    if(m.rows == rows && m.cols == cols)
        return m;

    if(m.rows < rows)
    {
        m.vals = realloc(m.vals, rows * sizeof(float*));
        for(int i = m.rows; i < rows; i++)
            m.vals[i] = calloc(m.cols, sizeof(float));
        m.rows = rows;
    }
    if(m.cols < cols)
    {
        for(int i = 0; i < m.rows; i++)
            m.vals[i] = realloc(m.vals[i], cols*sizeof(float) );
        m.cols = cols;
    }
    
    return m;
}

matrix add(matrix m1, matrix m2)
{

}

matrix sub(matrix m1, matrix m2)
{
    matrix m3 = create(m1.rows, m1.cols);
    for(int i = 0; i < m1.rows; i++)
        for(int j = 0; j < m2.rows; j++)
            m3.vals[i][j] = m1.vals[i][j] - m2.vals[i][j];
    return m3;
}

float *toArray(matrix m1, int row, int column, int axis)
{

}


matrix loadCifarBatch(char *batchPath)
{
    FILE *fp = fopen(batchPath, "r");
    if(!fp)
        perror("The following Error occurred : ");
    
    matrix m;
    m.rows = 10000;
    m.cols = 3072;
    
    m.vals = calloc(m.rows, sizeof(float *));
    
    for(int i = 0; i < m.rows; i++)
        m.vals[i] = calloc(m.cols, sizeof(float));
    
    
    fseek(fp, 1, SEEK_SET);
    
    for(int count = 0; count < 3072; count++)
        m.vals[0][count] = fgetc(fp);
    
    fseek(fp, 3074, SEEK_SET);
    
    for(long int i = 1; i <m.rows; i++)
    {
        if(i != 1)
            fseek(fp, 1, SEEK_CUR);
        for(int j = 0; j < m.cols; j++)
            m.vals[i][j] = fgetc(fp);
    }

    return m;
}

matrix loadCifarLabels(char *batchPath)
{
    FILE *fp = fopen(batchPath, "r");
    if(!fp)
        perror("The following Error occurred : ");

    matrix m;
    m.rows = 10000;
    m.cols = 1;

    m.vals = calloc(m.rows, sizeof(float *));
    
    for(int i = 0; i < m.rows; i++)
        m.vals[i] = calloc(m.cols, sizeof(float));

    m.vals[0][0] = fgetc(fp);
    fseek(fp, 1, SEEK_SET);

    for(int i = 1; i < m.rows; i++)
    {
        fseek(fp, 3072, SEEK_CUR);
        m.vals[i][0] = fgetc(fp);
    }
    return m;

}


/* 
 * Collate support is Cocked up for now. Still not gonna use Function Overloading. More like I can't :\
 * TODO - Implement _Generic (No, not the Java one. That's shit tbh)
 */

matrix collate(matrix *m1, matrix *m2, matrix *m3, matrix *m4, matrix *m5)
{
    matrix m;
    m.rows = m1->rows + m2->rows + m3->rows + m4->rows + m5->rows;
    m.cols = m1->cols;
    m.vals = calloc(m.rows, sizeof(float *));
    
    for(int i = 0; i < m.rows; i++)
        m.vals[i] = calloc(m.cols, sizeof(float));

    for(int i = 0; i < m.rows; i++)
        for(int j = 0; j < m.cols; j++)
        {   
            if(i < m1->rows)
                m.vals[i][j] = m1->vals[i][j];

            else if(i >= m1->rows && i < m1->rows * 2)
                m.vals[i][j] = m2->vals[i - m1->rows][j];

            else if(i >= m1->rows * 2 && i < m1->rows * 3)
                m.vals[i][j] = m3->vals[i - (m1->rows * 2)][j];

            else if(i >= m1->rows * 3 && i < m1->rows * 4)
                m.vals[i][j] = m4->vals[i - (m1->rows * 3)][j];

            else if(i >= m1->rows * 4)
                m.vals[i][j] = m5->vals[i - (m1->rows * 4)][j];
        }
    return m;
}

float * min(matrix *m ,int axis)
{
    float *minValues = (float *)calloc(m->rows, sizeof(float *));
    float *pos = (float *)calloc(m->rows, sizeof(float *));
    for(int i = 0; i < m->rows; i++)
    {
        minValues[i] = m->vals[i][0];
        pos[i] = 0;
        for(int j = 1; j < m->cols; j++)
            if(m->vals[i][j] < minValues[i])
            {
                minValues[i] = m->vals[i][j];
                pos[i] = j;
            }
    }
    
    free(minValues);
    return pos;
}

/*
int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

matrix sort(matrix m, int axis)
{
    if(axis == 1)
    {
        float *temp = (float *)calloc(m.cols, sizeof(float *));
        for(int i = 0; i < m.rows; i++)
        {
            for(int j = 0; j < m.cols; j++)
                temp[j] = m.vals[i][j];

            qsort(temp, m.cols, 8, compare);
            for(int j = 0; j < m.cols; j++)
                m.vals[i][j] = temp[j];
        }
    }

    else if(axis == 0)
    {

    }

    return m;
}
*/

#endif