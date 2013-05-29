#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE (1)

#define MAXNAME (20)

//Declares the structure used for grade entries. 
struct grade_entry {
    char name[ MAXNAME+1 ] ;
    int  grade ;
} ;

#define MAXGRADES (100)

int numgrades = 0 ;
struct grade_entry grade_list[ MAXGRADES ] ;

// Declaration of the program's functions.

extern void sort_by_name();
extern void sort_by_grade();
extern void print_grades();
extern void compute();

int main(){

	int done;
	int i = 0;
	int grade;

	
	do{
		done = scanf("%s %d",grade_list[i].name,&grade);
		if(done==EOF){
			break;
		}
		grade_list[i].grade=grade;
		i++;

	}while(TRUE);
	
	numgrades = i;

	printf("--Initial Ordering--\n");
	print_grades(numgrades);

	printf("--Sorted by Name--\n");
	sort_by_name(numgrades);
	print_grades(numgrades);
	
	printf("--Sorted by Grade--\n");
	sort_by_grade(numgrades);
	print_grades(numgrades);
	
	printf("------------------------\n");
	compute(numgrades);
}

/*
 * Prints the list of names and grades. 
 */

void print_grades(int numgrades){

	int i;
	for(i = 0; i < numgrades; i++){
		if(grade_list[i].grade != 0){

			printf("%s %d \n",grade_list[i].name, grade_list[i].grade);	
		}	
	}

}


// Sorts the list of structs based on name 
void sort_by_name(int numgrades){
	int i;
	int hole;
        struct grade_entry item;
	
	//Insertion sort algorithm 
	for(i = 0; i < numgrades; i++){
		item = grade_list[i];
		hole = i;
		while(hole > 0 && (strcmp(grade_list[hole-1].name, item.name) > 0 )){
			grade_list[hole] = grade_list[hole-1];
			hole -= 1;
			
		} 
		grade_list[hole] = item;
	}
	
}

// Sorts the list of structs based on grade 
void sort_by_grade(int numgrades){
	int i;
	int hole;
        struct grade_entry item;

	//Insertion sort algorithm	
	for(i = 0; i < numgrades; i++){
		item = grade_list[i];
		hole = i;
		while(hole > 0 && grade_list[hole-1].grade < item.grade){
			grade_list[hole] = grade_list[hole-1];
			hole -= 1;
			
		} 
		grade_list[hole] = item;
	}
	
}

//Preforms and prints the computations to find the mean and median grades. 
void compute(int numgrades){
	sort_by_grade(numgrades);
	int i;
	double median;
	int sumgrades = 0;
	double mean;

	//calculates the median and mean values. 
	for( i = 1; i <= numgrades; i++){
		if(((i) % 2) != 0){ // if grade is odd indexed
			median = (double) grade_list[ numgrades / 2 ].grade ;
		}
		else{
			median = (double) (grade_list[ (numgrades / 2) - 1 ].grade + grade_list[ numgrades / 2 ].grade) / 2.0 ;	
		}
		sumgrades += grade_list[i-1].grade;
	}

	printf("Sum of grades = %d \n Num of grades = %d\n",sumgrades,numgrades);

	mean = (double)sumgrades / (double)numgrades;
	
	printf("The median is %f\n", median);
	printf("The mean is %f\n", mean);
}
