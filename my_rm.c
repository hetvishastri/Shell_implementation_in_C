#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <dirent.h>

void remove_dir(char *dir_name){
	struct dirent **namelist;
	int n;
	int i;
	n=scandir(dir_name,&namelist,NULL,alphasort);
	for(i=2;i<n;i++){
		//creating path for all subdirectories and files
		char *path=malloc(strlen(dir_name)+strlen("/")+strlen(namelist[i]->d_name));
		strcpy(path,dir_name);
		strcat(path,"/");
		strcat(path,namelist[i]->d_name);
		struct stat filei;
		int file_status=stat(path,&filei);
		//run the loop till file is found
		if(S_ISDIR(filei.st_mode)){
			remove_dir(path);
		}
		else{
			remove(path);
		}
	}
	//after deleting all files delete empty directory
	remove(dir_name);
}
int my_rm(int argc, char* argv[]){
	int i;
	struct stat sb;
	
	if(argc==2){
		remove(argv[1]);
	}
	//removing directory using -r flag
	else if(argc==3 && strcmp("-r",argv[1])==0 ){
		if(stat(argv[2],&sb)==-1){
			printf("error\n");
		}
		else{
			
			if(S_ISDIR(sb.st_mode) || S_ISREG(sb.st_mode)){
				remove_dir(argv[2]);
				printf("remove directory\n");

			}
			else{
				printf("argument given was not directory");
			}
		}
	
	}
	// if multiple files given without r flag then files must be deleted
	else if(argc>2 && strcmp("-r",argv[2])!=0){
		for(i=1;i<argc;i++){
			if(stat(argv[i],&sb)==-1){
				printf("%s no such file directory present",argv[i]);
			}
			else{
				remove(argv[i]);
			}
		}
	}
	else{
		printf("error");
	}
}
	
