#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#define RESTRICTED 'X'
#include "symulacja.h"
#include "wyjscie.h"
#include "struct.h"
// Funkcja zwraca ilosc zywych sasiadow na podstawie sasiedztwa von Neumanna
int Neumann(matrix_t inputMatrix, int i, int j) {
    int neighboursAlive = 0;
    if(inputMatrix->macierz[(i) * inputMatrix->y + (j-1)] == '1')
        neighboursAlive++;
    if(inputMatrix->macierz[(i+1) * inputMatrix->y + (j)] == '1')
        neighboursAlive++;
    if(inputMatrix->macierz[(i) * inputMatrix->y + (j+1)] == '1')
        neighboursAlive++;
    if(inputMatrix->macierz[(i-1) * inputMatrix->y + (j)] == '1')
        neighboursAlive++;
    return neighboursAlive;

}
// Funkcja zwraca ilosc zywych sasiadow na podstawie sasiedztwa Moore'a
int Moore(matrix_t inputMatrix, int i, int j){
    int neighboursAlive = 0;
    if(inputMatrix->macierz[(i-1) * inputMatrix->y + (j-1)] == '1')
        neighboursAlive++;
    if(inputMatrix->macierz[(i+1) * inputMatrix->y + (j-1)] == '1')
        neighboursAlive++;
    if(inputMatrix->macierz[(i+1) * inputMatrix->y + (j+1)] == '1')
        neighboursAlive++;
    if(inputMatrix->macierz[(i-1) * inputMatrix->y + (j+1)] == '1')
        neighboursAlive++;
    return neighboursAlive + Neumann(inputMatrix, i,j);

}
//Funkcja wykonuje ruch w grze w życie, rodzajSasiedztwa to zmienna logiczna 1 dla Moore'a, 0 dla von Neumanna
void sasiedztwo(matrix_t inputMatrix, matrix_t outputMatrix, int rodzajSasiedztwa) {
    for (int i = 1; i < inputMatrix->x-1; i++) {
        for (int j = 1; j < inputMatrix->y - 1; j++) {
            int neighboursAlive = 0;
            if(rodzajSasiedztwa == 1)
                neighboursAlive = Moore(inputMatrix,i, j);
            else
                neighboursAlive = Neumann(inputMatrix, i, j);
            if (inputMatrix->macierz[(i) * inputMatrix->y + (j)] == '1') {
                if (neighboursAlive == 2 || neighboursAlive == 3)
                    outputMatrix->macierz[(i) * outputMatrix->y + (j)] = '1';
                else
                    outputMatrix->macierz[(i) * outputMatrix->y + (j)] = '0';
            } else if (inputMatrix->macierz[(i) * inputMatrix->y + (j)] == '0') {
                if (neighboursAlive == 3)
                    outputMatrix->macierz[(i) * outputMatrix->y + (j)] = '1';
                else
                    outputMatrix->macierz[(i) * outputMatrix->y + (j)] = '0';
            }
        }
    }

}
// Funkcja do iteracji. Korzysta z prawie wszystkich powyższych funkcji
void iterateXTimes(matrix_t inputMatrix, matrix_t outputMatrix, int iterations, int NoFirst, int signature, int rodzajSasiedztwa, int dialog, char*dirname) {
    int Actual = 1;
    for(int i=0; i< iterations; i++) {
        if(Actual<NoFirst)
        {
            sasiedztwo(inputMatrix,outputMatrix,rodzajSasiedztwa);
            matrix_t temp = inputMatrix;
            inputMatrix = outputMatrix;
            outputMatrix = temp;
            i--;
            Actual++;
            continue;
        }
        sasiedztwo(inputMatrix,outputMatrix,rodzajSasiedztwa);
        matrix_t temp = inputMatrix;
        inputMatrix = outputMatrix;
        outputMatrix = temp;
        char txt='n', png='n';
        if(dialog == 1){
            printf("Numer generacji: %d (%d)\n",Actual+i,i+1);
            printMatrix(inputMatrix);
            printf("Wpisz 2 znaki (y lub n) okreslajace czy plansza ma byc zapisana do .txt lub/i png\n Przyklad : yn oznacza zapis do .txt bez png\n Wpisz q jesli chcesz zakonczyc dzialanie programu\n");
            scanf("%c%c", &txt, &png);
            if(txt != 'y' &&  png != 'y' && txt != 'n' && png != 'n'){
				if(txt != 'q' && png != 'q')
					printf("Nieprawidlowy znak. Program zakonczy dzialanie.\n");
				else printf("Wpisano komende zamknięcia. Program zakonczy dzialanie.\n");
                return;
            }
        }
        if(txt=='y' || dialog == 0) printMatrixToFile(inputMatrix,NoFirst+i,signature,dirname);
        if(png=='y' || dialog == 0){
            printMatrixToPNG(inputMatrix,NoFirst+i,signature,dirname);
        }
        if(compareContents(inputMatrix,outputMatrix) == 0) {
            printf("\nKazda nastepna plansza 'Gry w zycie' bedzie wygladala jak powyzsza, dlatego przerwano generacje\n");
            return;
        }
    }
}

//Porównuje zawartość macierzy, zwraca 1 gdy nie są takie same
int compareContents(matrix_t inputMatrix, matrix_t outputMatrix) {
    for (int i = 0; i < inputMatrix->x; i++) {
        for (int j = 0; j < inputMatrix->y; j++) {
            if(outputMatrix->macierz[i * inputMatrix->y + j] != inputMatrix->macierz[i * inputMatrix->y + j])
                return 1;
        }
    }
    return 0;
}
