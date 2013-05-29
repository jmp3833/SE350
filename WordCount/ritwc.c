#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE  (1)

int main() {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */
	int nchar; 		/* next read character */
	char charSet[] = { '\n' }; /* Contains special characters */
	char previous = 5;

	while((nchar = getchar() ) != EOF ){
		
		if(strchr( charSet, nchar) != NULL){
			++tot_lines;
		}

		if (( nchar == ' ') || ( nchar == '\n')){
   			if((previous != '\n') && (previous != ' ')){
				++tot_words;
			}
		}
		++tot_chars;
		previous = nchar;
	}
	

	
	printf("\n%d ",tot_lines);
	printf("%d ",tot_words);
	printf("%d ",tot_chars);

	return 0 ;
}
