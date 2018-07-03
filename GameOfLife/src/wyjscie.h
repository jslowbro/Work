#ifndef _WYJSCIE_H_
#define _WYJSCIE_H_
#include "struct.h"
//Macierz na konsole
void printMatrix(matrix_t matrix1);
//Funckja drukuje macierz do pliku nazwanego na podstawie unikatowej sygnatury i numeru generacji
void printMatrixToFile(matrix_t inputMatrix, int gen, int signature, char* dirname);
void printMatrixToPNG(matrix_t inputMatrix, int gen, int signature, char* dirname);
#endif