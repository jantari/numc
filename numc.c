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
	if (argc < 3) printf("Usage: numc [decimal number] [target number system] [-v]\n");
	else
	{
		if (strtol(argv[1], NULL, 10) > pow(10,18)-1 || strtol(argv[1], NULL, 10) < 0) printf("\nOnly positive numbers of up to 18 digits are supported currently.");
		else
		{
			if (strtol(argv[2], NULL, 10) < 2 || strtol(argv[2], NULL, 10) > 36) printf("\nOnly number systems on base 2 - 36 are supported currently.");
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
		}
	}
	// Programmende
	printf("\n\n");
	return 0;
}
