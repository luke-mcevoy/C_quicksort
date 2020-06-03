sort: sort.o quicksort.o
	gcc sort.o quicksort.o -o sort
sort.o: sort.c
	gcc -Wall -Werror -pedantic-errors -c sort.c
quicksort.o: sort.c quicksort.h
	gcc -Wall -Werror -pedantic-errors -c quicksort.c
clean:
	rm -f *.o sort sort.exe


##########################################################################################
#								Questions / Concerns
#	1) Is quicksort.h done correctly?
#	2) How to make the makefile?
#	3) How does swap work exactly?
#	4) Algorithm explanation in regards to C?
#	5) Requirements of sort.c and file reading
#
#	Function Pointers? : "will be passed to the quicksort function to tell it what
#						  what function to use to compare the element of the list."
#
#	<getopt.h> in sort.c and use getopts to parse the command line args.
#
#	Main issue is understanding and implementing swap
#
#	How do I account for different byte sizes of data types (doubles, int, char)
#
####################################################################################

####################################################################################
#								Plan of Design
#	1) Start with the getopts and usage message
#	2) Check if quicksort.h is right
#	3) Learn how to implement pointer functions with different data types
#	4) Learn how to read files and allocate space / parse through contents
#	5) Finish swap function
#	6) Lomutos, qs, qshelper
#	7) Have to use the comparison operation for functions
####################################################################################

####################################################################################
#								OH Questions
# 	1) Need help with reading file and putting it into an array
# 	2) Have the getopts working so that file is checked if exists when passed in with associated flag
#		(A) returning EXIT_FAILURE for file_check helper
# 		(B) Once file is found, call quicksort on array
# 	3) How to do the make file correctly
#	4) Look over the current quicksort
#	5) How the comps work
####################################################################################


