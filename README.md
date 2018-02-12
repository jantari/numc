# numc
A command line utility to convert numbers between number systems, written in C

## Usage:

    numc (number) -s (source number system) -t (target-number-system) [-v]

The optional "-v" argument enables verbose mode and outputs additional information about the calculation process.

## Examples:

`numc 42 -s10 -t2`    
Converts 42 (decimal) to binary

`numc 101010 -s2 -t10`    
Converts 101010 (binary) to decimal

`numc AFFE -s 16 -t 8`    
Converts AFFE (hexadecimal) to octal
