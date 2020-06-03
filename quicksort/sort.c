/*******************************************************************************
 * Name        : sort.c
 * Author      : Luke McEvoy
 * Date        : February 21, 2020
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

typedef enum {
    STRING,
    INT,
    DOUBLE
} elem_t;

/**
 * Basic structure of sort.c:
 *
 * Parses args with getopt.
 * Opens input file for reading.
 * Allocates space in a char** for at least MAX_ELEMENTS strings to be stored,
 * where MAX_ELEMENTS is 1024.
 * Reads in the file
 * - For each line, allocates space in each index of the char** to store the
 *   line.
 * Closes the file, after reading in all the lines.
 * Calls quicksort based on type (int, double, string) supplied on the command
 * line.
 * Frees all data.
 * Ensures there are no memory leaks with valgrind. 
 */

void error_message() {
	printf("Usage: ./sort [-i|-d] [filename]\n");
	printf("   -i: Specifies the file contains ints.\n");
	printf("   -d: Specifies the file contains doubles.\n");
	printf("   filename: The file to sort.\n");
	printf("   No flags defaults to sorting strings.\n");
}


/* Boolean deems if input is integer or not */
bool get_integer(char *input, int *value) {
	long long i;
	if (sscanf(input, "%lld", &i) != 1) {
		return false;
	}
	*value = (int)i;
	return true;
}


/* Boolean deems if input is double or not */
bool get_double(char *input, double *value) {
	long double i;
	if(sscanf(input, "%Le", &i) != 1) {
		return false;
	}
	*value = (double)i;
	return true;
}


int main(int argc, char **argv) {

	// opt initialized for getopts
	int opt;

	// enumerator used as flag for future comparison pointer function
	elem_t type = STRING;

	// corner case for lack of argmunets
	if (argc <= 1) {
		error_message();
		return EXIT_FAILURE;
	}

	// getopts for flags i, d, or unknown
	while ((opt = getopt(argc, argv, ":id")) != -1) {
		switch (opt) {

			// flag is deemed for type int
			case 'i':
				type = INT;
				break;
			
			// flag is deemed for type double
			case 'd':
				type = DOUBLE;
				break;


			// flag is unknown, error message is thrown
			case '?':
				printf("Unknown option: '%c' received.\n", opt);
				error_message();
				return EXIT_FAILURE;
		}
	}
	
	// buffer space allocation
	char *buf = (char*)malloc(sizeof(char) * (MAX_STRLEN +1));

	// filename is grabbed from command line arguments using optind
	char *filename = argv[optind];

	// file pointer intialized to read file associated to filename variable
	FILE *fp = fopen(filename, "r");

	// if the contents of file pointer (filename) are null, throw standard error
	if (fp == NULL) {
		fprintf(stderr, "Failed to read from file '%s'. %s\n", filename, strerror(errno));
		return EXIT_FAILURE;
	}

	// contents of passed file are assumed to be STRING
	if (type == STRING) {

		// string array of string arrays intialized and allocated in memory
		char **array = (char **)malloc(sizeof(char*) * MAX_ELEMENTS);

		// counter initialized to deem number of lines in file
		int counter = 0;

		while (fgets(buf, MAX_STRLEN-1, fp)) {
			buf[strlen(buf) - 1] = '\0';
			char* temp = strdup(buf);
			
			// space is allocated in memory for every line of file
			array[counter] = (char *)malloc(sizeof(char) * MAX_STRLEN);
			
			// array is copied into temp string array pointer
			strcpy(array[counter], temp);

			// increment counter
			counter = counter + 1;
		}

		// quicksort main function called with STRING
		quicksort(array, counter, sizeof(char *), str_cmp);
		
		// displays sorted array of STRING
		for (int j = 0; j < counter; j++) {
			printf("%s\n", array[j]);
		}

		// close the file
		free(buf);
		free(array);
		fclose(fp);
		return EXIT_SUCCESS;
	}


	// contents of passed file are assumed to be INT
	if (type == INT) {

		// int array initialized and allocated in memory
		int *array = (int *)malloc(sizeof(int) * MAX_ELEMENTS);

		// buf space allocation is altered as usage is with INT instead of STRING
		buf = (char*)malloc(sizeof(int) * (MAX_STRLEN+1));

		// counter initialized
		int counter = 0;

		while(fgets(buf, MAX_STRLEN-1, fp)) {
			get_integer(buf, &array[counter]);
			counter = counter + 1;
		}

		// quicksort main function called with INT
		quicksort(array, counter, sizeof(int), int_cmp);

		// displays sorted array of INT
		for (int j = 0; j < counter; j++) {
			printf("%d\n", array[j]);
		}

		// close the file
		
		free(buf);
		free(array);
		fclose(fp);
		return EXIT_SUCCESS;
	}

	if (type == DOUBLE) {
		double *array = (double *)malloc(sizeof(double) * MAX_ELEMENTS);

		// buf space allocation is altered as usage is with DOUBLE instead of STRING
		buf = (char*)malloc(sizeof(double) * MAX_STRLEN+1);
		int counter = 0;
		while(fgets(buf, MAX_STRLEN-1, fp)) {
			get_double(buf, &array[counter]);
			counter++;
		}

		// quicksort main function called with DOUBLE
		quicksort(array, counter, sizeof(double), dbl_cmp);

		// displays sorted array of DOUBLE
		for (int j = 0; j < counter; j++) {
			printf("%f\n", array[j]);
		}

		// close the file
		free(buf);
		free(array);
		fclose(fp);
		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;

}