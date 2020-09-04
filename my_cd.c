#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int my_cd(int argc, char* argv[]){
	if(argc!=2){
		printf("Not enough arguments");
	}
	else{
		//chdir is the system call will change the directory for program in process
		chdir(argv[1]);
	}
	return 1;
}