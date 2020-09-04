#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int my_pwd(int argc, char* argv[]){
	if(argc!=1){
		printf("Not enough arguments");
	}
	else{
		//getcwd gets the current working directory path
		char current_direct[100];
		printf("%s\n",getcwd(current_direct,100));
	}
	return 1;
}