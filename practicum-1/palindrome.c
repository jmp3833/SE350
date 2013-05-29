#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
	
	int end = ((int)strlen(line)-1);//end index of the string
	int startcursor = 0;
	int endcursor = end-1;
        int i; // incrementation variable
	
	for(i = 0; i < end;i++){
		
	
		if(startcursor == endcursor){
			return 1;//is a palindrome
		}
		else if(startcursor < endcursor){

			if(tolower(line[startcursor]) == tolower(line[endcursor])){
				endcursor = retreat(endcursor,line);
				startcursor = advance(startcursor,end,line);
			}
			else{
				return 0;//is not a palindrome
			}
		}
	
	}	
	return;
}		
		

/*
 * Advance the left index until either (a) we find a letter or (b) we hit
 * the right end. Return the final index.
 */

int advance(int pos, int end, char line[]) {
	
	int cur = pos+1;

	while((!isalpha(line[cur])) && (cur < end)){
		cur+=1;
	}
	return cur;
}
	
/*
 * Retreat the right index until (a) we find a letter or (b) we hit the left
 * end.
 */

int retreat(int pos, char line[]) {
	
	int cur = pos-1;
	
	while((!isalpha(line[cur])) && (cur > 0)){
		cur-=1;
		
	}
	return cur;

}
