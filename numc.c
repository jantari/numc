<<<<<<< HEAD
// https://github.com/jantari

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

unsigned long long int other_to_decimal (char input[], int input_length, int source_num_sys, _Bool verbosemode);
void decimal_to_other (unsigned long long int input, unsigned int target_num_sys, _Bool verbosemode);
void print_help (void);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_help();
		exit(0);
	}
	// Variablendeklaration
	int target_num_sys = 0, source_num_sys = 0;
	_Bool verbosemode = 0;
	unsigned long long int decimalNum = 0;

	// Using getopt
	int option = 0;
	while ((option = getopt(argc, argv, "s:t:hv")) != -1) {
        switch (option) {
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

	char *input;
	int input_length = 0;

	for (int index = optind; index < argc; index++) {
		if (argv[optind]) {
			input_length = strlen(argv[index]);
			input = malloc(input_length * sizeof(char) + 1);
			strcpy(input, argv[index]);
		} else {
			printf("Please specify a number to convert.");
			exit(-1);
		}
	}

	for (unsigned int iterate = 0, currentValue = 0; iterate < input_length; iterate++) {
		if (input[iterate] > '9') {
			currentValue = input[iterate] - '7';
		} else {
			currentValue = input[iterate] - '0';
		}
		if (currentValue >= source_num_sys) {
			printf("%s is not a valid number in the %i-number system.\n", input, source_num_sys);
			exit(-1);
		}
	}

	// Hauptprogramm
	if (source_num_sys != 10) {
		// Berechnung andere Zahlensysteme zu Dezimal (Routine 1)
		decimalNum = other_to_decimal(input, input_length, source_num_sys, verbosemode);
	}
	if (target_num_sys != 10) {
		// Berechnung Dezimal zu anderen Zahlensystemen	(Routine 2)
		if (source_num_sys != 10) {
			decimal_to_other(decimalNum, target_num_sys, verbosemode);
		} else {
			decimal_to_other(atol(input), target_num_sys, verbosemode);
		}
	} else {
		printf("%llu", decimalNum);
	}
	// Programmende
	free(input);
	if (verbosemode == 1) putchar('\n');
	putchar('\n');
	return 0;
}

unsigned long long int other_to_decimal (char input[], int input_length, int source_num_sys, _Bool verbosemode) {
	unsigned long long int valueOfDigit = 1, endzahl2 = 0;

	for (int position = 0; position != input_length; position++) {
		if (input[position] != '0') {
			if (input[position] > '9') valueOfDigit = input[position] - '7';
			else { valueOfDigit = input[position] - '0'; }

			endzahl2 += valueOfDigit * pow(source_num_sys, input_length - position - 1);	
		}
		if (verbosemode == 1) {
			printf("\n%d ^ %d: %i", source_num_sys, input_length - position - 1, (int)pow(source_num_sys, input_length - position - 1));
			printf("\nPosition: %i --- Value: %c", position, input[position]);
			printf("\n>> Result so far: %llu\n",endzahl2);
		}
	}

	if (verbosemode == 1) printf("\n%s(%d) in decimal is: %llu\n", input, source_num_sys, endzahl2);

	return endzahl2;
}

void decimal_to_other (unsigned long long int input, unsigned int target_num_sys, _Bool verbosemode) {
	// Allocate memory for a string with enough characters to hold the result of the calculation
	char *output = malloc((int)(log(input) / log(target_num_sys) + 2) * sizeof(char));

	if (verbosemode == 1) {
		printf("Allocated memory for '%f (rounded down) + 2' chars to store result.\n\n", (log(input) / log(target_num_sys) ) * sizeof(char));
	}

    int i = 0;
	static char numberArray[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	for (; input != 0; i++) {
		output[i] = numberArray[input % target_num_sys];

		if (verbosemode == 1) {
			printf("i: %i ----------- \tquotient:\t%llu\tremainder:\t%c\n", i, input, output[i]);
		}

		input /= target_num_sys;
	}
	output[i] = '\0';

	do {
		putchar(output[--i]);
	} while (i >= 0);

	free(output);
}

void print_help (void) {
	printf("Usage: numc (input number) -s (input number system) -t (target-number-system) [-v]\n");
=======
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
	if (argc < 2) {
		print_help();
		exit(0);
	}
	// Variablendeklaration
	int target_num_sys = 0, source_num_sys = 0;
	_Bool verbosemode = 0;
	unsigned long long int endzahl2 = 0;

	// Using getopt
	int option = 0;
	while ((option = getopt(argc, argv, "s:t:hv")) != -1) {
        switch (option) {
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

	char *input;
	int input_length = 0;

	for (int index = optind; index < argc; index++) {
		if (argv[optind]) {
			input_length = strlen(argv[index]);
			input = malloc(input_length * sizeof(char) + 1);
			strcpy(input, argv[index]);
		} else {
			printf("Please specify a number to convert.");
			exit(-1);
		}
	}

	for (unsigned int iterate = 0, currentValue = 0; iterate < input_length; iterate++) {
		if (input[iterate] > '9') {
			currentValue = input[iterate] - '7';
		} else {
			currentValue = input[iterate] - '0';
		}
		if (currentValue >= source_num_sys) {
			printf("%s is not a valid number in the %i-number system.\n", input, source_num_sys);
			exit(-1);
		}
	}

	// Hauptprogramm
	if (source_num_sys != 10) {
		// Berechnung andere Zahlensysteme zu Dezimal (Routine 1)
		endzahl2 = other_to_decimal(input, input_length, source_num_sys, verbosemode);
		// Ausgabe 
		if (verbosemode == 1) printf("\n%s(%d) in decimal is: ", input, source_num_sys);
		else if (verbosemode == 1) printf("%llu\n",endzahl2);
	}
	if (target_num_sys != 10) {
		// Berechnung Dezimal zu anderen Zahlensystemen	(Routine 2)
		if (source_num_sys != 10) {
			decimal_to_other(endzahl2, target_num_sys, verbosemode);
		} else {
			decimal_to_other(atol(input), target_num_sys, verbosemode);
		}
	} else {
		printf("%llu",endzahl2);
	}
	// Programmende
	putchar('\n');
	if (verbosemode == 1) putchar('\n');
	return 0;
}

unsigned long long int other_to_decimal (char input[], int input_length, int source_num_sys, _Bool verbosemode) {
	unsigned long long int divergebnis = 1, endzahl2 = 0;

	for (int position = 0; position != input_length; position++) {
		if (input[position] != 48)
		{
			if (input[position] > 57) divergebnis = input[position] - 55;
			else if (input[position] < 58) divergebnis = input[position] - 48;

			endzahl2 += divergebnis * pow(source_num_sys, input_length - position - 1);	
		}
		if (verbosemode == 1)
		{
			printf("\n%d ^ %lu: %i", source_num_sys, input_length - position - 1, (int)pow(source_num_sys, input_length - position - 1));
			printf("\nPosition: %i --- Value: %c", position, input[position]);
			printf("\n>> Result so far: %llu\n",endzahl2);
		}
	}

	return endzahl2;
}

void decimal_to_other (unsigned long long int input, unsigned int target_num_sys, _Bool verbosemode) {
	// Allocate memory for a string with enough characters to hold the result of the calculation
	char *output = malloc((int)(log(input) / log(target_num_sys) + 2) * sizeof(char));

	if (verbosemode == 1) {
		printf("Allocated memory for '%f (rounded down) + 2' chars.\n", (log(input) / log(target_num_sys) ) * sizeof(char));
	}

    int i = 0;
	static char numberArray[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	for (; input != 0; i++) {
		output[i] = numberArray[input % target_num_sys];

		if (verbosemode == 1) {
			printf("\ni: %i ----------- \tquotient:\t%llu\tremainder:\t%c", i, input, output[i]);
		}

		input /= target_num_sys;
	}
	output[i] = '\0';
	
	if (verbosemode == 1) {
		putchar('\n');
	}

	do {
		putchar(output[--i]);
	} while (i >= 0);

	free(output);
}

void print_help (void) {
	printf("Usage: numc (input number) -s (input number system) -t (target-number-system) [-v]\n");
>>>>>>> 32af276a1ddb74180221e7f5b528334956825dd1
}