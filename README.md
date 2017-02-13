# numc
A command line program to convert numbers between number systems, written in C

## Usage:

numc number [source number system] target-number-system [-v]

If no source number system is given, a decimal number (base 10) is assumed.
The optional "-v" argument enables verbose mode and outputs additional information about the calculation process.

## Examples:

    numc 42 2
Converts 42 (decimal) to binary

    numc 101010 2 10
Converts 101010 (binary) to decimal

    numc AFFE 16 8
Converts AFFE (hexadecimal) to octal
