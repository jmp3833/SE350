/*
 * Implementation of the read_data module.
 *
 * See read_data.h for a description of the read_data function's
 * specification.
 *
 * Note that the parameter declarations in this module must be
 * compatible with those in the read_data.h header file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read_data.h"

void read_data( char *character, int *integer, double *dprecision ) {

	//Scan the string and store into 3 pointers.
	
	scanf("%c$%i$%lf$",character,integer,dprecision);
	
	return ;
}
