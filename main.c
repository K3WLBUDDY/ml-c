#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char **argv)
{

    matrix m1 = loadCifarBatch("datasets/cifar10/data_batch_1.bin");
    matrix m2 = loadCifarBatch("datasets/cifar10/data_batch_2.bin");
    matrix m3 = loadCifarBatch("datasets/cifar10/data_batch_3.bin");
    matrix m4 = loadCifarBatch("datasets/cifar10/data_batch_4.bin");
    matrix m5 = loadCifarBatch("datasets/cifar10/data_batch_5.bin");

    matrix Xtr = collate(&m1, &m2, &m3, &m4, &m5);

    delete(m1);
    delete(m2);
    delete(m3);
    delete(m4);
    delete(m5);

    return 0;
}