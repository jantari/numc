// 07.02.2017 DDMMYYYY
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
	unsigned long long int divergebnis = 1;
	
	// Kontrollmechanismen von hier bis Hauptprogramm
	if (argc < 3) printf("Syntax: Binaer Dezimalzahl Zahlensystem [-v]\n");
	else
	{
		if (strtol(argv[1], NULL, 10) > pow(10,9)-1 || strtol(argv[1], NULL, 10) < 0) printf("\nMomentan werden keine Zahlen mit mehr als 9 Stellen, oder kleiner als 0 unterstuetzt.");
		else
		{
			if (strtol(argv[2], NULL, 10) < 2 || strtol(argv[2], NULL, 10) > 36) printf("\nMomentan werden nur Zahlensysteme von 2 bis 36 unterstuetzt.");
			else
			{
				// Hauptprogramm
				if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v"))
				{
					printf("\n*** VERBOSE MODE ***\n");
					for (args = argc; args >= 0; args--) printf("\nargv[%i]: %s", args, argv[args]);
					printf("\n");
				}
				// Berechnung
				for (divergebnis = strtol(argv[1], NULL, 10); divergebnis != 0; divergebnis = divergebnis / strtol(argv[2], NULL, 10), i++)
				{
					// Wenn rest jemals > 90 = ung�ltig! (90 = Z in ASCII)
					if (divergebnis % strtol(argv[2], NULL, 10) < 10) endzahl[i] = divergebnis % strtol(argv[2], NULL, 10) + 48; //ASCII Werte fuer rest<9
					else if (divergebnis % strtol(argv[2], NULL, 10) > 9 ) endzahl[i] = divergebnis % strtol(argv[2], NULL, 10) + 55; //ASCII Werte fuer rest>9 (Buchstaben)
					if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v"))
					{
						printf("\ni: %i ----------- Rechnung:\t%llu",i,divergebnis % strtol(argv[2], NULL, 10));
						printf("\tRest:\t%c\tDivErgebnis:\t%llu",endzahl[i], divergebnis);
					}
				}
				if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v")) printf("\n");
				// Ausgabe
				printf("\n%s ist im %s-ersystem: ",argv[1],argv[2]);
				do
				{
					i = i -1;
					printf("%c", endzahl[i]);
				} while (i >= 0);
       		}
		}
	}
	// Programmende
	printf("\n");
	return 0;
}