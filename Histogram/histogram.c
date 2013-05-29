#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE  (1)

#define NLETTERS (26)	/* size of array, one entry per letter */
#define MAXSTARS (70)	/* maximum number of stars in a histogram line */

int count[NLETTERS] ;	/* counts for each of the 26 letters */
	

/*
 * The declaration for the function to print a sequence of asterisks.
 */

extern void print_stars( int ns ) ;

int main() {

	int nchar; //selected character in the text file

	//Change character to uppercase, and add the count to the array
	while (( nchar = getchar() ) != EOF){
		if(isalpha(nchar)){
			nchar = toupper(nchar);
			count[(nchar -'A')] ++;
		}
	}
	
	//print the values in the array
	int i;
	int max = 0;
	for(i = 0; i < NLETTERS; i++){
		if (count[i] > max){
			max = count[i];
		} 
	}

	for (i = 0; i < NLETTERS; i++){
		printf("%c ", i + 'A');
		print_stars((MAXSTARS * count[i])/max);
	}


	return 0 ;
}

/*
 * Print out 'ns' stars (asterisks)
 */

void print_stars( int ns ) {
	int i;
	for(i = 0; i < ns; i++){
		printf("*");
	}
	printf("\n");
	return ;
}
