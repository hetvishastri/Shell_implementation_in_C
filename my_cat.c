#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
int my_cat(int argc, char *argv[]){
	//initializing file pointer
	FILE *fp;
	//buffer is initialize to stre thr read file and in one go it can read 60 characters
	char buffer[60];
	int i;
	if(argc==1){
		fprintf(stderr,"Usage: %s <pathname>\n",argv[0]);
		return 0;
	}
	else{
		for(i=1;i<argc;i++){
			//to check whether the input is file else it will result into error
			struct stat fb_stat;
			if((stat(argv[i],&fb_stat)==-1)){
				printf("%s : file does not exist\n",argv[i]);
			}
			else if(S_ISREG(fb_stat.st_mode)){
				fp=fopen(argv[i],"r");
				if(fp==NULL){
					printf("cat:cannot open file\n");
					return 1;
				}
				//fgets store the read file in buffer and stores 60 characters in one go
				while(fgets(buffer,60,fp)!=NULL){
					printf("%s",buffer);
				}
				fclose(fp);
			}
			else{
				printf("%s : Is not a file\n",argv[i]);
			}

		}
	}
	
}