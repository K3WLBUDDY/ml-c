#ifndef MATRIX_H
#define MATRIX_H

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
    
}

void scale(matrix m, float scale)
{
    for(int i = 0; i < m.rows; i++)
        for(int j = 0; j < m.cols; j++)
            m.vals[i][j] *= scale;
}

void loadFromCSV(char *filePath)
{
    //TODO
}

void dot(matrix m1, matrix m2)
{
    //TODO
}


matrix loadCifarBatch(char *batchPath)
{
    FILE *fp = fopen(batchPath, "r");
    if(!fp)
        perror("The following Error occurred : ");
    
    matrix m;
    int c;
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

/* 
 * Collate support is Cocked up for now. Still not gonna use Function Overloading. More like I can't :\
 * TODO - Implement _Generic (No, not the Java one. That's shit tbh)
 */

matrix collate(matrix *m1, matrix *m2, matrix *m3, matrix *m4, matrix *m5)
{
    matrix Xte;
    Xte.rows = m1->rows + m2->rows + m3->rows + m4->rows + m5->rows;
    Xte.cols = m1->cols + m2->cols + m3->cols + m4->cols + m5->cols;
    Xte.vals = calloc(Xte.rows, sizeof(float *));
    
    for(int i = 0; i < Xte.rows; i++)
        Xte.vals[i] = calloc(Xte.cols, sizeof(float));
    for(int i = 0; i < Xte.rows; i++)
        for(int j = 0; j < Xte.cols; j++)
        {   
            if(i < m1->rows)
                Xte.vals[i][j] = m1->vals[i][j];
            else if(i > m1->rows && i < m1->rows * 2)
                Xte.vals[i][j] = m2->vals[i][j];
            else if(i > m1->rows * 2 && i < m1->rows * 3)
                Xte.vals[i][j] = m3->vals[i][j];
            else if(i > m1->rows * 3 && i < m1->rows * 4)
                Xte.vals[i][j] = m4->vals[i][j];
            else 
                Xte.vals[i][j] = m5->vals[i][j];
        }
    return Xte;
}

#endif