#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "nnClassifier.h"

int main(int argc, char **argv)
{

    matrix x1 = loadCifarBatch("datasets/cifar10/data_batch_1.bin");
    matrix x2 = loadCifarBatch("datasets/cifar10/data_batch_2.bin");
    matrix x3 = loadCifarBatch("datasets/cifar10/data_batch_3.bin");
    matrix x4 = loadCifarBatch("datasets/cifar10/data_batch_4.bin");
    matrix x5 = loadCifarBatch("datasets/cifar10/data_batch_5.bin");
    matrix Xte = loadCifarBatch("datasets/cifar10/test_batch.bin");

    matrix Xtr = collate(&x1, &x2, &x3, &x4, &x5);

    delete(x1);
    delete(x2);
    delete(x3);
    delete(x4);
    delete(x5);

    matrix y1 = loadCifarLabels("datasets/cifar10/data_batch_1.bin");
    matrix y2 = loadCifarLabels("datasets/cifar10/data_batch_2.bin");
    matrix y3 = loadCifarLabels("datasets/cifar10/data_batch_3.bin");
    matrix y4 = loadCifarLabels("datasets/cifar10/data_batch_4.bin");
    matrix y5 = loadCifarLabels("datasets/cifar10/data_batch_5.bin");
    matrix Yte = loadCifarLabels("datasets/cifar10/test_batch.bin");

    matrix Ytr = collate(&y1, &y2, &y3, &y4, &y5);
    predict(&Xtr, &Ytr, &Xte);

    delete(y1);
    delete(y2);
    delete(y3);
    delete(y4);
    delete(y5);

    delete(Xtr);
    delete(Ytr);
    delete(Xte);
    delete(Yte);

    return 0;
}