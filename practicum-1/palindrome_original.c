#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLENGTH (80)

static int is_palindrome( char line[]);
static int advance(int pos, int end, char line[]) ;
static int retreat(int pos, char line[]) ;


/*
 * Driver main program for the palindrome program.
 * Read one line at a time from system input and 
 * calls is_palindrome function to determine if the 
 * line is a palindrome. Prints the line number and 
 * line contents if it is a palidrome, otherwise
 * nothing is printed. Program exits when end of
 * file is detected.
 */

/* DO NOT MODIFY THE MAIN FUNCTION */

int main(int ac, char **av) {
	char line[MAXLENGTH+1] ;
	int line_number;

	for ( line_number = 1 ; fgets(line, MAXLENGTH, stdin) ; line_number++ ) {
		if ( is_palindrome(line) ) {
			printf( "%d: %s\n", line_number, line) ;
		}
	}
	return 0 ;
}


/*
 * Check the provided line for a palindrome using adavnce() to 
 * move the left index from start of line and retreat() to move
 * the right index from the end of the line.
 * Returns 0 if not a palindrome, 1 if a valid palindrome
 */

int is_palindrome(char line[]) {

	int i; //Incrementation variable
	int eos_index = (strlen(line)-1); // end of string position

	int endval; // End value
	int startval; // Start value

	int startcursor = 0; //Keeps track of cursor from beginning
	int endcursor = eos_index; //Keeps track of cursor from end


	for(i = 0; i < strlen(line); i++){
		
		if(startcursor == endcursor){
			return 1; /*is a palindrome */
		}

		else if(startcursor > endcursor){
			if ((startcursor == endcursor +1) && (tolower(startval) == tolower(endval))){
				return 1; /*is a palindrome */ 
			}
			break;
		}

		else if(startcursor < endcursor){	
		
			startcursor = i;
			endcursor = (strlen(line)-1)-i;
		
			endval = line[endcursor];
			startval = line[startcursor];
		

			if(tolower(startval) != tolower(endval)){
				break;
			}
			
			startcursor = advance(i,eos_index,line);
			endcursor = retreat(endcursor,line);

		}
		
	}

	return 0 ; /* not a palindrome */
}

/*
 * Advance the left index until either (a) we find a letter or (b) we hit
 * the right end. Return the final index.
 */

int advance(int pos, int end, char line[]) {
	
	while(!(isalpha(line[pos])) ){
		if(pos != end){
			pos += 1;
		}
	}

	return pos ;
}

/*
 * Retreat the right index until (a) we find a letter or (b) we hit the left
 * end.
 */

int retreat(int pos, char line[]) {

	while(!(isalpha(line[pos]))){
		if(pos != 0){
			pos -= 1;
		}
	}

	return pos ;
}
