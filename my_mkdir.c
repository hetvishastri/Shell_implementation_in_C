#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int my_mkdir(int argc, char* argv[]){
    //0777 is for owner group and onw who have permission to read and write
    if(mkdir(argv[1],0777)==-1){
        fprintf(stderr,"%s already exits\n",argv[1]);
    }
    return 1;
}