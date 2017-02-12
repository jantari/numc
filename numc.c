// https://github.com/jantari

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	// Variablendeklaration
	int i = 0, args = 0;
	char endzahl[60];
	unsigned long long int divergebnis = 1, endzahl2 = 0;

	// Kontrollmechanismen von hier bis Hauptprogramm
	if (argc < 3) printf("Usage: numc input-number [input number system] target-number-system [-v]\n");
	else if (strtol(argv[1], NULL, 10) > pow(10,18)-1 || strtol(argv[1], NULL, 10) < 0) printf("\nOnly positive numbers of up to 18 digits are supported currently.");
	else if (strtol(argv[2], NULL, 10) < 2 || strtol(argv[2], NULL, 10) > 36) printf("\nOnly number systems on base 2 - 36 are supported currently.");
	else if (argc > 3)
	{
		if (strcmp(argv[3], "-v") && strtol(argv[3], NULL, 10) < 2 || strtol(argv[3], NULL, 10) > 36) printf("\nOnly number systems on base 2 - 36 are supported currently.");
	}
	// printf("\nHauptprogrammroutine startet!\n");
	// Hauptprogramm
	for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v"))
	{
		printf("\n*** VERBOSE MODE ***\n");
		for (args = argc; args >= 0; args--) printf("\nargv[%i]: %s",args, argv[args]);
	}
	for (args = argc -1; args > 2; args--) if (!strcmp(argv[args], "-v")) printf("\n");
	if (argc > 3 && strcmp(argv[3], "-v"))
	{
		// Berechnung andere Zahlensysteme zu Dezimal
		for (int position = strlen(argv[1]); position >= 0; position--)
		{
			if (argv[1][position] != 0) divergebnis = argv[1][position] - 48;
			endzahl2 = endzahl2 + divergebnis * pow(strtol(argv[2], NULL, 10),position - 1);
			for (args =argc - 1; args > 2; args--) if(!strcmp(argv[args], "-v"))
			{
				printf("\n%s hoch %i: %i",argv[2],position-1,(int)pow(strtol(argv[2], NULL, 10),position - 1));
				printf("\nargv[1][POSITION]: %i",argv[1][position] - 48);
				printf("\nposition, position -1: %i, %i",position, position -1);
				printf("\nENDZAHL2: %llu\n",endzahl2);
			}
		}
		// Ausgabe
		printf("\n%s(%s) on base %s is: %llu",argv[1],argv[2],argv[3],endzahl2);
	}
	else
	{
		// Berechnung Dezimal zu anderen Zahlensystemen	
		for (divergebnis = strtol(argv[1], NULL, 10); divergebnis != 0; divergebnis = divergebnis / strtol(argv[2], NULL, 10), i++)
		{
			// Wenn rest jemals > 90 = ungültig! (90 = Z in ASCII)
			if (divergebnis % strtol(argv[2], NULL, 10) < 10) endzahl[i] = divergebnis % strtol(argv[2], NULL, 10) + 48; //ASCII Werte fuer rest<9
			else if (divergebnis % strtol(argv[2], NULL, 10) > 9 ) endzahl[i] = divergebnis % strtol(argv[2], NULL, 10) + 55; //ASCII Werte fuer rest>9 (Buchstaben)
			if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v"))
			{
				printf("\ni: %i ----------- calculation:\t%llu",i,divergebnis % strtol(argv[2], NULL, 10));
				printf("\tremainder:\t%c\tquotient:\t%llu",endzahl[i], divergebnis);
			}
		}
		if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v")) printf("\n");
		// Ausgabe
		printf("\n%s on base %s is: ",argv[1],argv[2]);
		do
		{
			i = i -1;
			printf("%c", endzahl[i]);
		} while (i >= 0);
      	}	
	// Programmende
	printf("\n\n");
	return 0;
}
