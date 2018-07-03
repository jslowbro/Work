#ifndef _SYMULACJA_H_
#define _SYMULACJA_H_

#include "struct.h"
// Funkcja zwraca ilosc zywych sasiadow na podstawie sasiedztwa von Neumanna
int Neumann(matrix_t inputMatrix, int i, int j);
// Funkcja zwraca ilosc zywych sasiadow na podstawie sasiedztwa Moore'a
int Moore(matrix_t inputMatrix, int i, int j);
//Funkcja wykonuje ruch w grze w życie, rodzajSasiedztwa to zmienna logiczna 1 dla Moore'a, 0 dla von Neumanna
void sasiedztwo(matrix_t inputMatrix, matrix_t outputMatrix, int rodzajSasiedztwa);
// Funkcja do iteracji. Korzysta z prawie wszystkich powyższych funkcji
void iterateXTimes(matrix_t inputMatrix, matrix_t outputMatrix, int iterations, int NoFirst, int signature, int rodzajSasiedztwa, int dialog, char*dirname);

int compareContents(matrix_t inputMatrix, matrix_t outputMatrix);

#endif