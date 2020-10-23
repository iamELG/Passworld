clang:
	clang -Weverything -pedantic -o main main.c 
	
gcc:
	gcc -W -Wall -pedantic -o main main.c 

cppcheck:
	cppcheck main.c
