#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#define RESTRICTED 'X'
#include "symulacja.h"
#include "wyjscie.h"
#include "argcheck.h"
#include "struct.h"
#include <time.h>

#define SASIEDZTWO 1
/*
    1 - Sasiedztwo Moore'a
    2 - Sasiedztwo von Neumanna
*/
#define ILOSC_GENERACJI 10
#define NUMER_PIERWSZEJ 0 /* generacja 0 -> generacja wzieta z pliku wejsciowego */
#define DIALOG 0

// Alokuje pustą macierz o określonych rozmiarach
matrix_t createNewMatrix(int x, int y) {
    matrix_t newMatrix = (matrix_t)malloc(sizeof(struct matrix));
    newMatrix->macierz = (char*)malloc(sizeof(char*)*(y)*(x));
    newMatrix->x = x;
    newMatrix->y = y;
    return newMatrix;
}
// Tworzy macierz na podstawie pliku
matrix_t createMatrixFromFile(char* filename){
    FILE *f = fopen(filename,"r");
    int length;
    int height;
    fscanf(f,"%d %d", &length, &height);
    matrix_t newMatrix = createNewMatrix(length+2,height+2);
    char buf;
    for(int i = 1; i<newMatrix->x-1 && !feof(f); i++){
        for(int j = 1; j<newMatrix->y-1 && !feof(f); j++){
            buf=fgetc(f);
            if(buf == '1' || buf == '0')
                newMatrix->macierz[i*newMatrix->y + j] = buf;
            if(buf==' ' || buf == '\n' || buf == '\r') j--;
        }
    }
    for(int i=0;i<newMatrix->x;i++)
    {
        newMatrix->macierz[i]=newMatrix->macierz[(newMatrix->y-1)*(newMatrix->x)+i]='X';
    }
    for(int i=0;i<newMatrix->y;i++)
    {
        newMatrix->macierz[i*newMatrix->x]=newMatrix->macierz[(i+1)*(newMatrix->x)-1]='X';
    }

    fclose(f);

    return newMatrix;
}
void copyContentsMatrix(matrix_t inputMatrix, matrix_t outputMatrix) {
    for (int i = 0; i < inputMatrix->x; i++) {
        for (int j = 0; j < inputMatrix->y; j++) {
            outputMatrix->macierz[i * inputMatrix->y + j] = inputMatrix->macierz[i * inputMatrix->y + j];
        }
    }
}
int main(int argc, char**argv) {
    srand(time(NULL));
    int arg_data[]={SASIEDZTWO, ILOSC_GENERACJI, NUMER_PIERWSZEJ, DIALOG};
    int returnCode = CHECK(argc, argv, arg_data);
    if(returnCode) return returnCode; /* zwraca kod bledu wykryty podczas sprawdzania argumentow, danych wejsciowych i katalogu wyjsciowego */

    FILE * inputFile = fopen(argv[1],"r");
    if(inputFile == NULL)
    {
        printf("Nie uzyskano dostepu do pliku wejsciowego w module glownym programu. Dostep zostal zabroniony lub plik zostal usuniety po fazie sprawdzania danych podanych przez uzytkownika.\n");
        return 26;
    }
    DIR * outputCatalog = opendir(argv[2]);
    if(outputCatalog == NULL)
    {
        fclose(inputFile);
        printf("Nie uzyskano dostepu do katalogu wyjsciowego w module glownym. Dostep zostal zabroniony lub katalog zostal usuniety po fazie sprawdzania danych podanych przez uzytkownika.\n");
        return 27;
    }
	int randomNumber = 0;
	randomNumber = rand()%(10000-1) + 1;
    matrix_t macierz1 = createMatrixFromFile(argv[1]);
    matrix_t macierz2 = createNewMatrix(macierz1->x,macierz1->y);
    copyContentsMatrix(macierz1,macierz2);
    iterateXTimes(macierz1,macierz2,arg_data[1],arg_data[2],randomNumber,arg_data[0],arg_data[3], argv[2]);


    fclose(inputFile);
    closedir(outputCatalog);
    free(macierz1->macierz);
    free(macierz1);
    free(macierz2->macierz);
    free(macierz2);

    return 0;
}


