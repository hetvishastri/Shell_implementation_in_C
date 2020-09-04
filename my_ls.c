#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
int my_ls(int argc, char *argv[])
{
    //dirent stuct used to store inode number and name of the file or directory
	struct dirent **namelist;
	int n;
	int i;
    //status for checking whether directory is empty or not
	int status=0;
    //scandir stores names of file or directory in struct namelist
	if(argc==1){
        //alphasort is passed for alphabetical order of files and directories
		n=scandir(".",&namelist, NULL,alphasort);
	}
	else if(argc==2){
		n=scandir(argv[1],&namelist,NULL,alphasort);	
	}
	if(n<0)
	{
		fprintf(stderr,"scandir: No such file or directory exists\n");
		return 0;
	}
	
	else{
		//started from 2 as "." and ".." should not be printed
		for(i=2;i<=n-1;i++){
			status=1;	
			printf("%s ",namelist[i]->d_name);
			free(namelist[i]);	
		}
		//
		if(status==1){
			printf("\n");
		}
		free(namelist);
	}
	return 1;
	
}