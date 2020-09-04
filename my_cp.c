#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
int my_cp(int argc, char * argv[]){
	if(argc<3){
		fprintf(stderr,"Usage: %s <pathname>\n",argv[0]);
	}
	else{
		//
		if(argc==3){
			int file_stat;
			struct stat fb1;
			struct stat fb2;
			char buffer;
			FILE *file1;
			FILE *file2;
			//if the file to be copied doesn't exists
			if(stat(argv[1],&fb1)==-1){
				printf("%s: File doesn't exits\n",argv[1]);
				return 1;
			}
			//if second argument is directory then copy file to directory with same name
			file_stat=stat(argv[2],&fb2);
			if(S_ISDIR(fb2.st_mode) && file_stat!=1){
				if(S_ISREG(fb1.st_mode)){
					printf("File to directory\n");
					//opening the file in write mode
					file1=fopen(argv[1],"r");
					//creating path
					char *path=malloc(strlen(argv[2])+strlen("/")+strlen(argv[1])+1);
					strcpy(path,argv[2]);
					strcat(path,"/");
					strcat(path,argv[1]);
					//opening the file in write mode
					file2=fopen(path,"w");
					//fgetc returns character
					while((buffer=fgetc(file1))!=EOF){
						//writing the character store in buffer into file2
						fputc(buffer,file2);
					}
					fclose(file1);
					fclose(file2);
				}
				else{
					printf("cp:ommitting directory\n");
				}
			}
			//if second argument doesn't exist or it is a file
			else{
				printf("file to file\n");
				file1=fopen(argv[1],"r");
				file2=fopen(argv[2],"w");
				while((buffer=fgetc(file1))!=EOF){
					fputc(buffer,file2);
				}
				fclose(file1);
				fclose(file2);
			}
		}
		else if(argc>3){

			if(strcmp("-r",argv[1])!=0){
				struct stat fbc;
				if(stat(argv[argc-1],&fbc)==-1){
					printf("%s:Directory doesn't exist\n",argv[argc-1]);
					return 1;
				}
				else if(S_ISDIR(fbc.st_mode)){
					printf("Files to directory\n");
					int i;
					for(i=1;i<argc-1;i++){
						struct stat fbi;
						char buffer;
						FILE *filei1;
						FILE *filei2;
						if(stat(argv[i],&fbi)==-1){
							printf("%s: File doesn't exits",argv[i]);
							return 1;
						}
						filei1=fopen(argv[i],"r");
						//creating path for files into directory
						char *path=malloc(strlen(argv[argc-1])+strlen("/")+strlen(argv[i])+1);
						strcpy(path,argv[argc-1]);
						strcat(path,"/");
						strcat(path,argv[i]);
						filei2=fopen(path,"w");
						while((buffer=fgetc(filei1))!=EOF){
							fputc(buffer,filei2);
						}
						fclose(filei1);
						fclose(filei2);	
					}
				}
			}
			else if(strcmp("-r",argv[1])==0){
				struct stat fb1;
				struct stat fb2;
				if(stat(argv[2],&fb1)==-1){
					printf("%s:Directory does not exist",argv[2]);
					return 1;
				}
				printf("Directory to directory\n");
				//creating second directory if it doesn't exist
				if(stat(argv[3],&fb2)==-1){
					if(S_ISDIR(fb2.st_mode)!=1){
						if(mkdir(argv[3],0777)==-1){
							perror("mkdir");
							return 1;
						}
					}

				}
				if(S_ISDIR(fb1.st_mode)){
					struct dirent **namelist;
					int n;
					int i;
					//creating path for first directory into second directory as subdirectory
					char *path1=malloc(strlen(argv[3])+strlen("/")+strlen(argv[2])+1);
					strcpy(path1,argv[3]);
					strcat(path1,"/");
					strcat(path1,argv[2]);
					
					//creating first directory inside second directory 
					if(mkdir(path1,0777)==-1){
						//if file already exists then copy command does nothing
						return 1;
					}
					//scanning files in first directory
					n=scandir(argv[2],&namelist,NULL,alphasort);

					if(n<0){
						perror("scandir");
					}
					char buffer;
					FILE *filei1;
					FILE *filei2;
					//copying files to directory one in second directory
					for(i=2;i<=n-1;i++){
						struct stat fbi;
						char buffer;
						char *path4=malloc(strlen(argv[2])+strlen("/")+strlen(namelist[i]->d_name)+1);
						strcpy(path4,argv[2]);
						strcat(path4,"/");
						strcat(path4,namelist[i]->d_name);
	
						int filei_stat=stat(path4,&fbi);
					
						if(!S_ISDIR(fbi.st_mode)){	
						
							//creating path for first directory files				
							char *path2=malloc(strlen(argv[2])+strlen("/")+strlen(namelist[i]->d_name)+1);
							strcpy(path2,argv[2]);
							strcat(path2,"/");
							strcat(path2,namelist[i]->d_name);
							//creating path writing in second directory
							char *path3=malloc(strlen(argv[3])+strlen("/")+strlen(argv[2])+strlen("/")+strlen(namelist[i]->d_name)+1);
							strcpy(path3,argv[3]);
							strcat(path3,"/");
							strcat(path3,argv[2]);			
							strcat(path3,"/");
							strcat(path3,namelist[i]->d_name);
							//open files in first directory in read mode
							filei1=fopen(path2,"r");
							//creating files in first directory in write mode
							filei2=fopen(path3,"w");
							while((buffer=fgetc(filei1))!=EOF){
								fputc(buffer,filei2);
							}
							free(namelist[i]);
						}	
					}
				}
				else{
					printf("Argument is not a directory");
				}						
				
			}
			else{
				printf("%s:Directory doesn't exist",argv[argc-1]);
				return 1;
			}
		}
	}
	
}
