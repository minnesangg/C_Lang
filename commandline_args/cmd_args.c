#include<stdio.h>
#include<stdlib.h>

void usage(char *programm_name){
    printf("Usage %s <message> <# of times to repeat\n", programm_name);
    exit(1);
}

int main(int argc, char *argv[]){
    int counter;

    if(argc < 3){
        usage(argv[0]);
    }

    counter = atoi(argv[2]);
    printf("Repeating %d times\n", counter);

    for(int i = 0; i < counter; i++){
        printf("%3d - %s\n", i, argv[1]);
    }
    return 0;
}