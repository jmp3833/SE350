#Main compile target
test_pointers:  main.o read_data.o 
	gcc -o test_pointers main.o read_data.o

#Compiles the main.c and read_data.c files into objects.
main.o: main.c read_data.h  
	gcc -c main.c
read_data.o: read_data.c read_data.h
	gcc -c read_data.c

#removes the object files once compiled and linked. 
cleanup:
	rm *.o
