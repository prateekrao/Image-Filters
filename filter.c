#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    // Define allowable filters
    char *filters = "begr";

    // Get filter alphabet and check if it exists
    char filter = getopt(argc, argv, filters);

    if (filter == '?')
    {
        printf("Invalid filter.\n");
        return 1;
    }

    // Check if user has entered only one filter
    if (getopt(argc, argv, filters) != -1)
    {
        printf("Only one filter allowed.\n");
        return 2;
    }

    // Ensure proper usage
    if (argc != 4)
    {
        printf("Usage: filter -[flag] inputfile outputfile\n");
        return 3;
    }

    // Remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];


    // Open input file
    FILE *input = fopen(infile, "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Open output file
    FILE *output = fopen(outfile, "w");
    if (output == NULL)
    {
        fclose(input);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    



