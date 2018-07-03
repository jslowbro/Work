#include "argcheck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int CHECK(int argc, char**argv, int *arg_data) /* DONE */
{
	int returnCode = 0;
	if(argc==1)
	{
		printf("Nie podano argumentow wywolania. Aby uruchomic program, prosze podac plik wejsciowy i katalog wyjsciowy.\nUzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
		return 1;
	}
	if(argc>1) /* Sprawdzenie, czy -h (--help) zostal poprawnie uzyty [bez innych argumentow wywolania] */
	{
		for(int i=1;i<argc;i++)
		{
			if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0)
			{
				if(argc!=2) /* Jezeli program zostal wywolany z innymi argumentami, zostanie on zakonczony */
				{
					printf("Argument wypisujacy pomoc zostal niepoprawnie uzyty. Aby uzyskac pomoc, prosze uzyc arugmentu -h lub --help BEZ wykorzystania innych argumentow.\n");
					return 2;
				}else{
					PRINT_HELP();
					return 3;
				}
			}
		}
	}

	/* Tu nastepuje sprawdzenie, czy zostanie wyrzucony jakis kod bledu. Lista kodow bledu znajduje sie na koncu tego pliku. */
	returnCode = CHECK_INPUT_FILE(argv[1]);
	if(returnCode)
	{
		return returnCode;
	}

	returnCode = CHECK_OUTPUT_CATALOG(argv[2]);
	if(returnCode)
	{
		return returnCode;
	}

	returnCode = CHECK_ARGS(argc,argv,arg_data);
	if(returnCode)
	{
		return returnCode;
	}
	/* Jezeli wystapi blad z ktoryms z argumentow, program zostanie zakocznony przed dotarciem do tego punktu. Jezeli nie wystapi zaden blad, oznacza to, ze argumenty wywolania i dane wejsciowe sa poprawne. */
	return 0;
}

void PRINT_HELP() 
{
	printf("Ponizej szablon wywolania programu wraz z opisami\n");
    printf("./gameoflife <input file.txt> <katalog wyjsciowy> [-s 1/2] [-ilosc generacji] [-g numer pierwszej] [-d] [-h --help]\n");
    printf("<input file.txt> to nazwa pliku zapisanego w .txt, ktory zawiera macierz z ktorej beda generowane kolejne macierze\n");
    printf("katalog wyjściowy to nazwa katalogu do ktorego generowane beda pliki .txt i .png\n");
    printf("-s sasiedztwo mowi o uzywanym sasiedztwie 1 to sasiedztwo Moora, 2 to sasiedztwo von Neumanna\n");
    printf("-n mowi o ilosci generacji ktore ma wygenerowac program\n");
    printf("-g mowi o numerze piewszej generacji ktora ma wygenerowac program (widoczne w pliku .txt lub .png)\n");
    printf("-d pozwala na dialog programu z uzytkownikiem\n");
    printf("-h lub --help wywoluje pomoc\n");
	
}

int CHECK_ARGS(int argc,char**argv,int*arg_data)
{
	int uzyte[]={0,0,0,0}; /* kolejno argumenty: s, n, g, d; tablica do sprawdzenia, czy ktorys z argumentow nie zostal uzyty wiecej niz jeden raz */
	for(int i=3;i<argc;i++)
	{
		if(strcmp(argv[i],"-s")==0 || strcmp(argv[i],"-n")==0 || strcmp(argv[i],"-g")==0 || strcmp(argv[i],"-d")==0)
		{
			if(strcmp(argv[i],"-s")==0) 
			{
				if(uzyte[0]==1)
				{
					printf("Argument -s powinien zostac uzyty jednokrotnie. Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
					return 6;
				}else uzyte[0]=1; /* oznaczenie argumentu -s jako wykorzystanego */

				if(i+1>=argc)
				{
					printf("Nie podano wartosci dla argumentu -s. Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
					return 10;
				}

				if(strcmp(argv[i+1],"1")!=0 && strcmp(argv[i+1],"2")!=0)
				{
					printf("Nieprawidlowa wartosc przy argumencie -s. (\"%s\"); Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n",argv[i+1]);
					return 11;
				}
				arg_data[0]=atoi(argv[i+1]); /* zapis danych do tablicy przechowującej informacje o argumentach */
				i++;
			}
			else if(strcmp(argv[i],"-n")==0) 
			{
				if(uzyte[1]==1)
				{
					printf("Argument -n powinien zostac uzyty jednokrotnie. Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
					return 7;
				}else uzyte[1]=1; /* oznaczenie argumentu -n jako wykorzystanego */

				if(i+1>=argc)
				{
					printf("Nie podano wartosci dla argumentu -n. Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
					return 12;
				}

				for(int j=0;j<strlen(argv[i+1]);j++)
				{
					if((int)argv[i+1][j]<48 || (int)argv[i+1][j]>57)
					{
						printf("Nieprawidlowa wartosc przy argumencie -n. (%s); Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n",argv[i+1]);
						return 13;
					}
				}
				arg_data[1]=atoi(argv[i+1]); /* zapis danych do tablicy przechowującej informacje o argumentach */
				i++;
			}
			else if(strcmp(argv[i],"-g")==0)
			{
				if(uzyte[2]==1)
				{
					printf("Argument -g powinien zostac uzyty jednokrotnie. Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
					return 8;
				}else uzyte[2]=1; /* oznaczenie argumentu -g jako wykorzystanego */
				
				if(i+1>=argc)
				{
					printf("Nie podano wartosci dla argumentu -g. Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
					return 14;
				}

				for(int j=0;j<strlen(argv[i+1]);j++)
				{
					if((int)argv[i+1][j]<48 || (int)argv[i+1][j]>57)
					{
						printf("Nieprawidlowa wartosc przy argumencie -g. (%s); Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n",argv[i+1]);
						return 15;
					}
				}
				arg_data[2]=atoi(argv[i+1]); /* zapis danych do tablicy przechowującej informacje o argumentach */
				i++;
			}
			if(strcmp(argv[i],"-d")==0)
			{
				if(uzyte[3]==1)
				{
					printf("Argument -d powinien zostac uzyty jednokrotnie. Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n");
					return 9;
				}else uzyte[3]=1; /* oznaczenie argumentu -d jako wykorzystanego */
				
				if(arg_data[3]) arg_data[3]=0; /* zapis danych do tablicy przechowującej informacje o argumentach */
				else arg_data[3]=1;
			}
		}else{
			printf("Nieznany argument \"%s\". Uzyj argumentu -h lub --help, aby uzyskac pomoc.\n",argv[i]);
			return 5;
		}
	}
	return 0;
}

int CHECK_INPUT_FILE(char*arg_input)
{
	FILE * checker = fopen(arg_input,"r");
	if(checker==NULL)
	{
		printf("Nie uzyskano dostepu do pliku \"%s\". Plik nie istnieje, lub dostęp do niego jest zablokowany.\n", arg_input);
		return 4;
	}
	int liczbaWierszy,liczbaKolumn;
	liczbaWierszy=liczbaKolumn=0;
	int nrLinii=1; /* liczba linii w pliku wejsciowym */
	char buf; /* bufor dla odczytu pliku wejsciowego */
	int sprawdzanieIlosciWierszy=1; /* zmienna logiczna, ktora oznacza, czy w danym momencie sprawdzana jest liczba wierszy, czy liczba kolumn macierzy */
	while((buf=fgetc(checker))!=EOF) /* petla pierwsza do zapisu wartosci dotyczacej wielkosci mapy automatu */
	{
		if(sprawdzanieIlosciWierszy) /* sprawdzenie ilosci wierszy mapy automatu */
		{
			if(((int)buf<48 || (int)buf>57) && buf!=' ' && buf!='\n' && buf!='\r')
			{
				printf("Podano nieprawidlowy znak w liczbie reprezentujacej ilosc wierszy (\"%c\"). Prosze podac liczbe calkowita dodatnia mniejsza lub rowna milion.\n",buf);
				fclose(checker);
				return 18;
			}
			if(buf!=' ' && buf!='\n' && buf!='\r')
			{
				if(liczbaWierszy)
				{
					liczbaWierszy*=10;
				}
				liczbaWierszy+=(int)(buf)-48;
				if(liczbaWierszy>1000000)
				{
					printf("Liczba wierszy automatu komorkowego jest za duza. Prosze wprowadzic liczbe mniejsza lub rowna milion.\n");
					fclose(checker);
					return 17;
				}
			} else {
				sprawdzanieIlosciWierszy=0;
				if(buf=='\n' || buf=='\r') nrLinii++;
			}
		}else{ /* sprawdzenie ilosci kolumn mapy automatu */
			if(((int)buf<48 || (int)buf>57) && buf!=' ' && buf!='\n' && buf!='\r')
			{
				printf("Podano nieprawidlowy znak w liczbie reprezentujacej ilosc kolumn (\"%c\"). Prosze podac liczbe calkowita dodatnia mniejsza lub rowna milion.\n",buf);
				fclose(checker);
				return 20;
			}
			if(buf!=' ' && buf!='\n' && buf!='\r')
			{
				if(liczbaKolumn)
				{
					liczbaKolumn*=10;
				}
				liczbaKolumn+=(int)(buf)-48;
				if(liczbaKolumn>1000000)
				{
					printf("Liczba kolumn automatu komorkowego jest za duza. Prosze wprowadzic liczbe mniejsza lub rowna milion.\n");
					fclose(checker);
					return 19;
				}
			} else {
				if(buf=='\n' || buf=='\r') nrLinii++;
				break;
			}
		}
	}
	if(buf==EOF)
	{
		printf("Wystapil blad przy odczycie pliku, lub osiagnieto koniec pliku w fazie odczytywania wielkosci mapy. Prosze zweryfikowac poczatkowe dane pliku wejsciowego.\n");
		fclose(checker);
		return 16;
	}
	/* Tutaj juz znane sa wymiary macierzy */
	double iloscKomorekAutomatu = liczbaWierszy * liczbaKolumn;

	/* Zanim plik zostanie zatwierdzony, zostaje on sprawdzony pod katem ewentulanych blednych znakow. Po sprawdzeniu i zatwierdzeniu pliku, zostanie on wczytany w pelni raz jeszcze w module glownym, gdzie zostanie zaalokowana pamiec dla macierzy. */

	double aktualnaSprawdzonaLiczbaKomorek = 0;
	while((buf=fgetc(checker))!=EOF)
	{
		if(buf!='0' && buf!='1' && buf!=' ' && buf!='\n' && buf!='\r')
		{
			printf("Znaleziono nieprawidlowy znak w linii %d (\"%c\"). Prosze usunac ten znak z pliku wejsciowego i uruchomic program jeszcze raz.\n", nrLinii, buf);
			fclose(checker);
			return 21;
		}
		if(buf==' ') continue;
		if(buf=='\n' || buf=='\r'){
			nrLinii++;
			continue;
		}
		aktualnaSprawdzonaLiczbaKomorek++;
	}

	if(aktualnaSprawdzonaLiczbaKomorek > iloscKomorekAutomatu)
	{
		printf("Przekroczono dopuszczalna liczbe komorek w pliku wejsciowym. Dla podanych wymiarow macierzy oczekiwana liczba komorek to %.0f, a podano %.0f.\n",iloscKomorekAutomatu, aktualnaSprawdzonaLiczbaKomorek);
		fclose(checker);
		return 22;
	}
	if(iloscKomorekAutomatu > aktualnaSprawdzonaLiczbaKomorek)
	{
		printf("Podano za mala liczbe komorek w pliku wejsciowym. Dla podanych wymiarow macierzy oczekiwana liczba komorek to %.0f, a podano %.0f.\n",iloscKomorekAutomatu,aktualnaSprawdzonaLiczbaKomorek);
		fclose(checker);
		return 23;
	}
	/* Jezeli program dotarl tutaj, oznacza to, ze dane wejsciowe sa poprawne */

	fclose(checker);
	iloscKomorekAutomatu=(liczbaWierszy+2)*(liczbaKolumn*2); /* dodanie dwoch wierszy i kolumn na zabezpieczenie przed wyjsciem poza tablice */
	if(iloscKomorekAutomatu>26214400) /* 25MB <- rozmiar jednej tablicy */
	{
		printf("Uwaga! Ze wzgledu na wymiary macierzy, konieczne bedzie zaalokowanie pamieci o wielkosci %.2f MB. Czy chcesz kontynuowac?\n",iloscKomorekAutomatu/524288); /* podzielone przez 1024*512, poniewaz alokowane jest miejsce na dwie dwuwymiarowe tablice o tych samych wymiarach */
		char wybor='\0';
		while(wybor!='n' && wybor!='N' && wybor!='t' && wybor!='T')
		{
			wybor='\0';
			printf("[T/N] Twoj wybor: ");
			scanf("%1s",&wybor);
		}
		if(wybor=='n' || wybor=='N') return 24;
	}
	return 0;
}

int CHECK_OUTPUT_CATALOG(char*arg_output)
{
	DIR * checker = opendir(arg_output);
	if(checker == NULL)
	{
		printf("Nie uzyskano dostepu do katalogu \"%s\". Katalog nie istnieje, dostep zostal zabroniony lub podana nazwa wskazuje na plik niebedacy katalogiem.\n",arg_output);
		return 25;
	}
	closedir(checker);
	return 0;
}

/*

Kody wyjscia:
0 - EXIT_SUCCESS
1 - brak argumentow
2 - niepoprawne uzycie argumentu -h lub --help
3 - (EXIT_SUCCESS) zakonczenie dzialania z arugmentem -h lub --help
4 - nie uzyskano dostepu do pliku wejsciowego (wyjscie z funkcji CHECK_INPUT_FILE)
5 - nieznany argument
6 - wielokrotne uzycie argumentu -s
7 - wielokrotne uzycie argumentu -n
8 - wielokrotne uzycie argumentu -g
9 - wielokrotne uzycie argumentu -d
10 - brak wartosci przy argumencie -s
11 - nieprawidlowa wartosc przy argumencie -s
12 - brak wartosci przy argumencie -n
13 - nieprawidlowa wartosc przy argumencie -n
14 - brak wartosci przy argumencie -g
15 - nieprawidlowa wartosc przy argumencie -g
16 - EOF przy odczycie danych z poczatku pliku wejsciowego
17 - za duza liczba wierszy macierzy
18 - nieprawidlowy znak w liczbie wierszy
19 - za duza liczba kolumn macierzy
20 - nieprawidlowy znak w liczbie kolumn
21 - znaleziono nieprawidlowy znak w danych dotyczacych komorek automatu
22 - w pliku wejsciowym jest podana za duza liczba komorek
23 - w pliku wejsciowym jest podana za mala liczba komorek
24 - przerwane przez uzytkownika (wybor opcji "NIE" po ostrzezeniu o zuzyciu pamieci)
25 - nie uzyskano dostepu do katalogu wyjsciowego (wyjscie z funkcji CHECK_OUTPUT_CATALOG)

*/