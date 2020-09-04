#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
int my_grep(int argc, char *argv[]){
	int i;
	if(argc==1){
		printf("grep:searchterm[file...]");
		
	}
	//if second argument is " " print full file
	if(!strcmp(argv[1],"\"") && !strcmp(argv[2],"\""))
	{
		FILE *fp;
		char *line=NULL;
		size_t len=0;
		ssize_t read;
		int i;
		//opens file in read mode
		for(i=3;i<argc;i++){
			fp=fopen(argv[i],"r");
			//error if file is corrupt or doesn't exist
			if(fp==NULL){
				printf("grep:cannot open file\n");
				return 0;
			}
			while((read=getline(&line,&len,fp))!=-1){
				printf("%s",line);
					
			}
		}
		
    }
	//if input is just grep search term and input terminal will open
	//to get out of this press ctrl+c but it will result into close of my_shell
	else if(argc==2){
		char *line=NULL;
		//size_t is used to calulate size in bytes and not able to represent negative number
		size_t len=0;
		//ssize_t is used to calulate size in bytes and able to represent negative number
		ssize_t read;
		while((read!=-1)){
			//reads entire line from stdin and stores address of text location in line 
			//len represents bytes 
			read=getline(&line,&len,stdin);
			if((strstr(line,argv[1])!=NULL)){
				printf("%s",line);
			}
		}		
	}
	else{
		for(i=2;i<argc;i++){
			FILE *fp;
			char *line=NULL;
			size_t len=0;
			ssize_t read;
			//opens file in read mode
			fp=fopen(argv[i],"r");
			//error if file is corrupt or doesn't exist
			if(fp==NULL){
				printf("grep:cannot open file\n");
				return 0;
				
			}
			while((read=getline(&line,&len,fp))!=-1){
				
				//strstr is used to find the search term in a line as a substring
				//just finds first occurrence
				if((strstr(line,argv[1])!=NULL)){
					printf("%s",line);
					}
			}
			free(line);
			fclose(fp);	
		}
			
	}
}

