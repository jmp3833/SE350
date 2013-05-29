/* Implementation of the The Sudoku puzzle module.
 *
 * In keeping with standard Sudoku nomenclature, we use
 * 1-based indexing. Thus row indices, column indices,
 * and digits being placed must all be in the range 1 .. 9.
 */

#include <stdlib.h>
#include <stdio.h>

#include "puzzle.h"
#include "bool.h"

/*
 * The tables are 10x10 so that we can index from 1 .. 9 (the 0th row
 * and column are ignored). This wastes a tad of space, but is much
 * less likely to cause "off by 1" indexing errors.
 *
 * puzzle[i][j] is the number (0 .. 9) at row i, column j.
 *   0 represents a free (blank) puzzle location.
 *   Anything else represents the value at that location, and
 *     must be consistent with the rules of Sudoku.
 *
 * fixed[i][j] is true <=> row i, column j is fixed.
 *   That is, the value was part of the initial puzzle layout and
 *   cannot be erased.
 */

static short puzzle[10][10] ;
static bool  fixed[10][10] ;

/*
 * Functions to determine whether a row, a column, or the "region"
 * containing a row and column, contains the specified digit.
 */
static bool row_contains(int row, int digit) ;
static bool col_contains(int col, int digit) ;
static bool region_contains(int row, int col, int digit) ;

/*
 * Function to determine whether an integer - not the character for
 * a digit - is in the range 0 .. 9.
 */
static bool in_range(int value) ;

/*
 * Print support functions.
 *   print a line of dashes.
 *   print a row of values (with blanks for 0's).
 */
static void print_dashes() ;
static void print_row(int row) ;

/*
 * Initialize the puzzle so that (a) all values are zero (free)
 * and (b) non of the values are 'fixed' (uneraseable).
 */

extern void init_puzzle()  {
	int row = 10; 
	int column = 10;
	
	//Incrementation variables
	int r; 
	int c;

	for(r = 1; r < row; r++){
		for(c = 1; c < column; c++){
			puzzle[r][c] = 0;
			fixed[r][c] = FALSE;
		}
	}
}
/*
 * Read in the initial puzzle configuration.
 * Each line is 4 characters long:
 *   Row    as a character '0' .. '9'
 *   Column as character '0' .. '9'
 *   Digit  as character '0' .. '9'
 *   Terminating newline.
 * Exits with an error message if there are syntactic
 * or semantic errors with any configuration line.
 */

void configure(FILE *puzzle_file) {

	char line[5];//line buffer
	int row;
	int column;
	int value;
	int line_count = 0;
	
	while(( fgets(line,5,puzzle_file)) != NULL){
		
	
		row = line[0]-'0';
		column = line[1]-'0';
		value = line[2]-'0';
	
		
		if(!in_range(row) || !in_range(column) || !in_range(value)){
			printf("Illegal format in configuration file at line %d ", line_count);
			exit(1);
		}
	
		if((puzzle[row][column] != 0)||(row_contains(row,value))||(col_contains(column,value))||(region_contains(row,column,value))){
			printf("Illegal placement in configuration file at line %d ",line_count);
			exit(1);
		}
		
	
		
	
		puzzle[row][column] = value;
		fixed[row][column] = TRUE;	
		line_count += 1;
	}

}
/*
 * Print the puzzle to standard output using the
* specified output format.
 * 	- Print an initial row of dashes.
 * 	- Print each row.
 * 	- Print a row of dashes after each 3rd row.
 */

void print_puzzle() {
	int r; // Incrementation variable

	print_dashes();

	for(r = 1; r < 10; r++){
		
		print_row(r);

		if (( r % 3 ) == 0 ){
			print_dashes();
		}	

	}
}
	
/*
 * (Attempt to) add the specified digit at the given row and
 * column location on the puzzle.
 * The digit, row, and column must all be integers in
 * the range 1 .. 9.
 *
 * Return value is the status of the attempt (OP_OK is the only
 * status where the puzzle is actually changed).
 */

op_result add_digit(int row, int col, int digit) {
	
	if(in_range(row)){
		if(in_range(col)){
			if(in_range(digit)){
				
				if(puzzle[row][col] != 0){
					return OP_OCCUPIED;
				}
				if((row_contains(row,digit))||(col_contains(col,digit))){
					return OP_ILLEGAL;
					
				}
				
				if(region_contains(row,col,digit)){
					return OP_ILLEGAL;
				}
				
				puzzle[row][col] = digit;		
				return OP_OK;
				
			}
		}
	}

	return OP_BADARGS ;
}

/*
 * (Attempt to) delete the digit at the given row and
 * column location on the puzzle the row and column
 * must both be integers in the range 1 .. 9
 *
 * Return value is the status of the attempt (OP_OK is the only
 * status where the puzzle actually changed).
 */

op_result erase_digit(int row, int col) {
	if(in_range(row)){
		if(in_range(col)){
			
			if(puzzle[row][col] == 0){
				return OP_EMPTY;
			}

			if(fixed[row][col] == TRUE){
				return OP_FIXED;	
			}
			
			puzzle[row][col] = 0;		
			return OP_OK;
		}
	}
	return OP_BADARGS ;
}



/*
 * Returns TRUE iff the given 'row' has the given 'digit' in it.
 */
static bool row_contains(int row, int digit) {

	int i;
	for(i = 1; i < 10; i++){
		if(puzzle[row][i] == digit){
			return TRUE;
		}
	}

	return FALSE ;
}

/*
 * Returns TRUE iff the given 'col' has the given 'digit' in it.
 */
static bool col_contains(int col, int digit) {
	
	int i;
	for(i = 1; i < 10; i++){
		if(puzzle[i][col] == digit){
			return TRUE;
		}
	}

	return FALSE ;

}

/*
 * Returns TRUE iff the region containing the cell at 'row' & 'col'
 * has the given digit in it.
 * NOTE: Finding the first row and column for the 'row'
 *       and 'col' is simple if you (a) remember that integer
 *       division discards the remainder and (b) translating
 *       the indices to 0 rather than 1 base makes things easier.
 * NOTE: A region is a 3 x 3 square.
 */
static bool region_contains(int row, int col, int digit) {
	
	//Incrementation variables

	int row_index;
	int col_index;

	if(row >= 1 && row <= 3){
		row_index = 1;
	}
	if(row >= 4 && row <= 6){
		row_index = 4;
	}
	if(row >= 7 && row <= 9){
		row_index = 7;
	}
	if(col >= 1 && col <= 3){
		col_index = 1;
	}
	if(col >= 4 && col <= 6){
		col_index = 4;
	}
	if(col >= 7 && col <= 9){
		col_index = 7;
	}

	int i;
	int j;

	for(i = row_index; i < row_index+3; i++){
		for(j = col_index; j < col_index + 3; j++){
			if(puzzle[i][j] == digit){
				return TRUE;
			}
		}	
	}

	return FALSE ;
}

/*
 * Ref(row >= 4 && row <= 6){
turn TRUE iff the value is in the Sudoku range (1 .. 9)
 */
static bool in_range(int value) {	
	int i; //Incrementation variable
	for( i = 0; i < 9; i++ ){
		if(value-1 == i){
			return TRUE;
		}
	}
	return FALSE ;
}

/*
 * Print a row of 25 dashes.
 * This will line up correctly with the rows with data.
 */
static void print_dashes() {
	printf("-------------------------\n");
}

/*
 * Print a row from the puzzle.
 *   Print an initial bar ('|').
 *   For each value in the row, print a space and either:
 *     - a space if the value is 0.
 *     - the CHARACTER code for the digit if non-zero.
 *   After the 3rd, 6th and 9th columns, print " |"
 */
static void print_row(int row) {


	int i;
	printf("|");
	for(i = 1; i < 10; i++){
		printf(" ");
		if(puzzle[row][i] == 0){
			printf(" ");
		}
		else{
			printf("%d",puzzle[row][i]);
		}

		if((i%3) == 0){
			printf(" |");
		}
	} 
	printf("\n");
}

