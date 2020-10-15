all:
	gcc -o main -Wall -Werror main.c
clang:
	clang -o login -lssl -lcrypto login.c
