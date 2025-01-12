#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    printf("RAND_MAX = %u\n", RAND_MAX);
    srand(time(0));

    printf("8 Numbers beside 0 and RAND_MAX:\n");
    for(int i = 0; i < 8; i++){
        printf("Number : %d\n", rand());
    }

    printf("8 Numbers beside 0 and 20:\n");
    for(int i = 0; i < 8; i++){
        printf("Number : %d\n", ((rand()%20)+1));
    }
    return 0;
}