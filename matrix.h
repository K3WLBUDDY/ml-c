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

matrix add(matrix m1, matrix m2)
{

}

matrix sub(matrix m1, matrix m2)
{

}

matrix multiply(matrix m1, int scalar)
{

}

float toArray(matrix m1, int axis)
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

#endif