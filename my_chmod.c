#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int my_chmod(int argc, char* argv[]){
    if(argc<3){
        printf("chmod: missing operand after %s",argv[2]);
    }
    else{
        struct stat fb;
        
        if(stat(argv[2],&fb)==-1){
            printf("chmod: cannot access %s :No such file or directory\n",argv[2]);

        }
        else{
            if(chmod(argv[2],strtol(argv[1],0,8))==-1){
                fprintf(stderr,"error");
            }
        }
    }
    return 1;
}