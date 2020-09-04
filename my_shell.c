#include "my_functionheaders.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
int my_execute(int argc,char *argv[]){
    //if-else statement for self made commands
	if(strcmp(argv[0],"\n")==0){
		return 1;
	}
	else if(strcmp(argv[0],"ls")==0){
		my_ls(argc,argv);
		return 1;
	}
	else if(strcmp(argv[0],"grep")==0){
		my_grep(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"cat")==0){
		my_cat(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"mv")==0){
		my_mv(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"cp")==0){
        my_cp(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"cd")==0){
		my_cd(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"pwd")==0){
		my_pwd(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"rm")==0){
		my_rm(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"chmod")==0){
		my_chmod(argc,argv);
		return(1);
	}
	else if(strcmp(argv[0],"mkdir")==0){
		my_mkdir(argc,argv);
		return(1);
	}
    //if the command is not found in self made commands it will run built-in commands
	else{
		int rc=fork();
		if(rc<0){
			fprintf(stderr,"fork failed");
		}
		else if(rc==0){
			// Child Process
			if(execvp(argv[0],argv)==-1){
				printf("error\n");
				return 0;				
			}

		}
		else{
			wait(NULL);
			return 1;
		}
	}	
}
char **my_parse(char *line){
	int buffer=1024;
	int pos=0;
    //dynamic allocation of array with buffer number of elements
	char **args_array=malloc(sizeof(char*) *buffer);
	char *tok_pat;
	if(!args_array){
		fprintf(stderr,"error\n");
		exit(1);
	}
	tok_pat=strtok(line," ");//pointer to first token
    //run till it reachesto NULL point
	while(tok_pat!=NULL){
		args_array[pos]=tok_pat;
		pos=pos+1;
        //if input size increases size of the buffer reallocate the memory
		if(pos>=buffer){
			buffer=buffer+1024;
			args_array=realloc(args_array,sizeof(char*) *buffer);
			if(!args_array){
				//storing error in stderr file
				fprintf(stderr,"error\n");
				exit(1);
			}
		}
		tok_pat=strtok(NULL," ");//setting the pointer to start next token
	}
	args_array[pos]=NULL;
	return args_array;
}
char *my_read(){
    //buffer is the maximum amount of characters
	int buffer=1024;
	int pos=0;
    //dynamic allocation of memory 
	char *line=malloc(sizeof(char) *buffer);
	int c;
    //if not able to allocate memory
	if(!line){
        //fprintf helps to store the error in the file here stderr
		fprintf(stderr,"my_shell:allocation error\n");
		exit(1);
	}
	while(1){
		
        //getchar() assigns integer to an unassigned character
		c=getchar();
		if(c==EOF || c=='\n'){
			line[pos]='\0';
			return line;
		}
		else{
			line[pos]=c;
		}
		pos=pos+1;
        //if input size increases size of the buffer reallocate the memory
		if(pos>=buffer){
			buffer=buffer+1024; 
			line=realloc(line,buffer);
			if(!line){
				fprintf(stderr,"my_shell:allocation error\n");
				exit(1);
			}
		}
	}
}
int my_invoke(char *argv[]){
	int argc=0;
    //check variable for checking for "&" in command
	int check=0;
    //while loop to count number of arguments
	while(argv[++argc]!=NULL);

	if(strcmp(argv[argc-1],"&")==0){
		check=1;
		argv[argc-1]=NULL;
		argc=argc-1;
		int status;
		pid_t rc1=fork();
		//if(check==1){
		//	printf("Child: Current process ID is: %d\n", (int)getpid());
		//}

		if(rc1<0){
			fprintf(stderr,"fork failed");
			exit(0);
		}
		else if(rc1==0){
			// Child Process
			//printf("child process started\n");
			my_execute(argc,argv);
			//printf("child process ended\n");
			exit(1);
			
		}
    }
	else{
		my_execute(argc,argv);
	}
	

	return 1;
}
void my_shell_loop(void){
	char *line;
	char **args;
	int status=1;
	
	while(status){
		printf("%s","myshell>> ");
        //For every command three process runs read, argument parsing and execution
		line=my_read();
		args=my_parse(line);
		status=my_invoke(args);
        //free command is used to free the memory for next command
        //free is used as we are dynamically allocating memory
		free(args);
		free(line);
	}
}
int main(int argc,char* argv[]){
	printf("\t\t\t----------------WELCOME TO MY SHELL-----------------\t\t\t\n");
	my_shell_loop(); //my_shell runs in a loop till ctrl+c is pressed
    exit(0);
}