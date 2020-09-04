#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
int my_mv(int argc,char *argv[])
{
	int i;
	if(argc<3){
		fprintf(stderr,"Usage: %s <pathname>\n",argv[0]);
	}
	else if(argc==3){
		//stat declared to know whether it is directory or not
		struct stat fb_stat1;
		struct stat fb_stat2;
		//if the file that is moved doesn't exit
		if(stat(argv[1],&fb_stat1)==-1){
			printf("File does not exits\n");
			return 1;
		}
		
		else{
			stat(argv[2],&fb_stat2);
			//if second argument is directory move file to directory
			if(S_ISDIR(fb_stat2.st_mode)){
				//creating a path for new file in directory
				char *path=malloc(strlen("./")+strlen(argv[2])+strlen("/")+strlen(argv[1])+1);
				strcpy(path,"./");
				strcat(path,argv[2]);
				strcat(path,"/");
				strcat(path,argv[1]);
				rename(argv[1],path);
				
			}
			//else create new file or owerwrite existing
			else{
				rename(argv[1],argv[2]);
				
			}
			return 1;
		}
				
	}
	else{
		struct stat fb_stati;
		struct stat fb_statc;
		if(stat(argv[argc-1],&fb_statc)==-1){
			printf("%s does not exits",argv[argc-1]);
			return 1;
		}
		//many files into directory
		if(S_ISDIR(fb_statc.st_mode)){
			for(i=1;i<argc-1;i++){
				if(stat(argv[i],&fb_stati)==-1){
					printf("File does not exits\n");
				}
				//creating a path for new file in directory
				char *path=malloc(strlen("./")+strlen(argv[argc-1])+strlen("/")+strlen(argv[i])+1);
				strcpy(path,"./");
				strcat(path,argv[argc-1]);
				strcat(path,"/");
				strcat(path,argv[i]);
				rename(argv[i],path);
			}
		}
		else{
			printf("%s directory does not exits\n",argv[argc-1]);
		}
	}
}