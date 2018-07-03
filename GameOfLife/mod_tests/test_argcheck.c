#include<stdio.h>
#include<stdlib.h>
#include "argcheck.h"

#define SASIEDZTWO 1
/*
	1 - Sasiedztwo Moore'a
	2 - Sasiedztwo von Neumanna
*/
#define ILOSC_GENERACJI 10
#define NUMER_PIERWSZEJ 1
#define DIALOG 0

int main(int argc, char**argv)
{
	int arg_data[]={SASIEDZTWO, ILOSC_GENERACJI, NUMER_PIERWSZEJ, DIALOG};
	int returnCode = CHECK(argc, argv, arg_data);
	printf("s:%d n:%d g:%d d:%d\n",arg_data[0],arg_data[1],arg_data[2],arg_data[3]);
	if(returnCode) return returnCode; /* zwraca kod bledu wykryty podczas sprawdzania argumentow, danych wejsciowych i katalogu wyjsciowego */
	return 0;
}