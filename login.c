#include <stdio.h>
#include <openssl/sha.h>
//#include <stdlib.h>
//#include <string.h>


//======================================================================
//======================================================================
int main(int argc, char *argv[]){

	unsigned char data[] = "test";
	unsigned char hash[SHA512_DIGEST_LENGTH];
	SHA512(data, sizeof(data) - 1, hash);
	printf("==========\n");
	printf("%s\n",hash);
	printf("==========\n");
	return 0;

}
	
