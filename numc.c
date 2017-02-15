// https://github.com/jantari

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	// Variablendeklaration
	int i = 0, args = 0, position = 0;
	char endzahl[60];
	unsigned long long int divergebnis = 1, endzahl2 = 0;

	// Kontrollmechanismen von hier bis Hauptprogramm
	if (argc < 3)
	{
		printf("Usage: numc input-number [input number system] target-number-system [-v]\n");
		return -1;
	}
	if (strtol(argv[1], NULL, 10) > pow(10,18)-1 || strtol(argv[1], NULL, 10) < 0)
	{
		printf("Only positive numbers of up to 18 digits are supported currently.\n");
		return -1;
	}
	if (strtol(argv[2], NULL, 10) < 2 || strtol(argv[2], NULL, 10) > 36)
	{
		printf("Only number systems on base 2 - 36 are supported currently.\n");
		return -1;
	}
	if (argc > 3 && strcmp(argv[3], "-v"))
	{
		if (strtol(argv[3], NULL, 10) < 2 || strtol(argv[3], NULL, 10) > 36)
		{
			printf("Only number systems on base 2 - 36 are supported currently.\n");
			return -1;
		}
		for (position = 0; position != strlen(argv[1]); position++)
		{
			if (argv[1][position] > 57)
			{
				if (argv[1][position] - 55 >= strtol(argv[2], NULL, 10))
				{
					printf("%s is not a valid number in the number system specified.\n",argv[1]);
					return -1;
				}
			}
			else if (argv[1][position] - 48 >= strtol(argv[2], NULL, 10))
			{
				printf("%s is not a valid number in the number system specified.\n",argv[1]);
				return -1;
			}
		}
	}
	// Hauptprogramm
	// Verbose Output
	for (args = 2; args < argc; args++) if (!strcmp(argv[args], "-v"))
	{
		for (args = 0; args < argc; args++) printf("\nargv[%i]: %s",args, argv[args]);
	}
	for (args = argc -1; args > 2; args--) if (!strcmp(argv[args], "-v")) printf("\n");
	if (argc > 3 && strcmp(argv[3], "-v"))
	{
		// Berechnung andere Zahlensysteme zu Dezimal (Routine 1)
		for (position = 0; position != strlen(argv[1]); position++)
		{
			if (argv[1][position] != 48)
			{
				if (argv[1][position] > 57) divergebnis = argv[1][position] - 55;
				else if (argv[1][position] < 58) divergebnis = argv[1][position] - 48;
				endzahl2 = endzahl2 + divergebnis * pow(strtol(argv[2], NULL, 10),strlen(argv[1]) - position - 1);	
			}
			// Verbose Output
			for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v"))
			{
				printf("\n%s ^ %lu: %i",argv[2],strlen(argv[1]) - position - 1,(int)pow(strtol(argv[2], NULL, 10),strlen(argv[1]) - position - 1));
				printf("\nPosition: %i --- Value: %llu",position,divergebnis);
				printf("\n>> Result so far: %llu\n",endzahl2);
			}
		}
		// Ausgabe 
		if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v")) printf("\n%s(%s) in decimal is: ",argv[1],argv[2]);
		if (!strcmp(argv[3], "10")) printf("%llu",endzahl2);
		else if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v")) printf("%llu\n",endzahl2);
	}
	if (argc < 4 || argc > 3 && strcmp(argv[3], "10"))
	{
		// Berechnung Dezimal zu anderen Zahlensystemen	(Routine 2)
		if (argc > 3 && strcmp(argv[3], "-v")) divergebnis = endzahl2;
		else divergebnis = strtol(argv[1], NULL, 10);

		for (; divergebnis != 0; i++)
		{
			// Wenn rest jemals > 90 = ungültig! (90 = Z in ASCII)
			if (argc > 3 && strcmp(argv[3], "-v"))
			{
				if (divergebnis % strtol(argv[3], NULL, 10) < 10) endzahl[i] = divergebnis % strtol(argv[3], NULL, 10) + 48; //ASCII Werte fuer rest<9
				else if (divergebnis % strtol(argv[3], NULL, 10) > 9 ) endzahl[i] = divergebnis % strtol(argv[3], NULL, 10) + 55; //ASCII Werte fuer rest>9 (Buchstaben)
			} else {
				 if (divergebnis % strtol(argv[2], NULL, 10) < 10) endzahl[i] = divergebnis % strtol(argv[2], NULL, 10) + 48; //ASCII Werte fuer rest<9
                                else if (divergebnis % strtol(argv[2], NULL, 10) > 9 ) endzahl[i] = divergebnis % strtol(argv[2], NULL, 10) + 55; //ASCII Werte fuer rest>9 (Buchstaben)
			}
			// Verbose Output
			if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v"))
			{
				printf("\ni: %i ----------- calculation:\t%llu",i,divergebnis % strtol(argv[2], NULL, 10));
				printf("\tremainder:\t%c\tquotient:\t%llu",endzahl[i], divergebnis);
			}
			if (argc > 3 && strcmp(argv[3], "-v")) divergebnis = divergebnis / strtol(argv[3], NULL, 10);
			else divergebnis = divergebnis / strtol(argv[2], NULL, 10);
		}
		// Ausgabe
		if (argc > 3)
		{
			for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v") && args != 3)  printf("\n\n%s(%s) on base %s is: ",argv[1],argv[2],argv[3]);
			if (!strcmp(argv[3], "-v")) printf("\n\n%s(%s) in decimal is: ",argv[1],argv[2]);
                }
                do
                {
                        i = i -1;
                        printf("%c", endzahl[i]);
                } while (i >= 0);
	}
	// Programmende
	if (argc > 3) for (args = argc - 1; args > 2; args--) if (!strcmp(argv[args], "-v")) printf("\n");
	printf("\n");
	return 0;
}
