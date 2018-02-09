// https://github.com/jantari

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

unsigned long long int other_to_decimal (char input[], int source_num_sys, _Bool verbosemode);
void decimal_to_other (unsigned long long int input, unsigned int target_num_sys, _Bool verbosemode);
void print_help (void);

int main(int argc, char *argv[])
{
	// Variablendeklaration
	int target_num_sys = 0, source_num_sys = 0;
	char endzahl[60];
	char input[60];
	_Bool verbosemode = 0;
	unsigned long long int endzahl2 = 0;

	// Using getopt
	int option = 0;
	int index;
    while ((option = getopt(argc, argv, "i:s:t:hv")) != -1) {
        switch (option)
        {
        case 'i':
            if(!strcpy(input, optarg)) {
                printf("Wrong command line argument: %s\n", optarg);
                exit(-1);
            }
            break;
        case 's':
            if(!(source_num_sys = atoi(optarg))) {
                printf("Wrong command line argument: %s\n", optarg);
                exit(-1);
            }
            break;
        case 't':
            if(!(target_num_sys = atoi(optarg))) {
                printf("Wrong command line argument: %s\n", optarg);
                exit(-1);
            }
            break;
        case 'h':
            print_help();
            exit(0);
            break;
        case 'v':
            verbosemode = 1;
            break;
        default:
            break;
        }
	}

	for (index = optind; index < argc; index++) {
		printf ("Non-option argument %s\n", argv[index]);
	}

	for (int iterate_through_string = 0; iterate_through_string < strlen(input); iterate_through_string++) {
		int ia = input[iterate_through_string] - '0';
		if (ia > source_num_sys) {
			printf("%s is not a valid number in the %i-number system.\n", input, source_num_sys);
			exit(-1);
		}
	}

	// Hauptprogramm
	if (source_num_sys != 10) {
		// Berechnung andere Zahlensysteme zu Dezimal (Routine 1)
		endzahl2 = other_to_decimal(input, source_num_sys, verbosemode);
		// Ausgabe 
		if (verbosemode == 1) printf("\n%s(%d) in decimal is: ", input, source_num_sys);
		if (target_num_sys == 10) printf("%llu",endzahl2);
		else if (verbosemode == 1) printf("%llu\n",endzahl2);
	}
	if (target_num_sys != 10) {
		// Berechnung Dezimal zu anderen Zahlensystemen	(Routine 2)
		if (source_num_sys != 10) {
			decimal_to_other(endzahl2, target_num_sys, verbosemode);
		} else {
			decimal_to_other(atol(input), target_num_sys, verbosemode);
		}
	}
	// Programmende
	putchar('\n');
	if (verbosemode == 1) putchar('\n');
	return 0;
}

unsigned long long int other_to_decimal (char input[], int source_num_sys, _Bool verbosemode) {
	unsigned long long int divergebnis = 1, endzahl2 = 0;

	for (int position = 0; position != strlen(input); position++) {
		if (input[position] != 48)
		{
			if (input[position] > 57) divergebnis = input[position] - 55;
			else if (input[position] < 58) divergebnis = input[position] - 48;

			endzahl2 += divergebnis * pow(source_num_sys, strlen(input) - position - 1);	
		}
		if (verbosemode == 1)
		{
			printf("\n%d ^ %lu: %i", source_num_sys, strlen(input) - position - 1, (int)pow(source_num_sys, strlen(input) - position - 1));
			printf("\nPosition: %i --- Value: %c", position, input[position]);
			printf("\n>> Result so far: %llu\n",endzahl2);
		}
	}

	return endzahl2;
}

void decimal_to_other (unsigned long long int input, unsigned int target_num_sys, _Bool verbosemode) {
	char output[60];
    int i = 0;

	for (; input != 0; i++) {
		if ((input % target_num_sys) < 10) {
			output[i] = input % target_num_sys + 48; // ASCII Werte fuer rest<10
		} else {
			output[i] = input % target_num_sys + 55; // ASCII Werte fuer rest>9 (Buchstaben)
		}

		if (verbosemode == 1) {
			printf("\ni: %i ----------- \tquotient:\t%llu\tremainder:\t%c", i, input, output[i]);
		}

		input = input / target_num_sys;
	}
	
	output[i] = '\0';
	if (verbosemode == 1) {
		putchar('\n');
	}

	do {
		i--;
		putchar(output[i]);
	} while (i >= 0);
}

void print_help (void) {
	printf("Usage: numc -i input-number -s input number system -t target-number-system [-v]\n");
}