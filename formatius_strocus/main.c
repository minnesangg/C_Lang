#include<stdio.h>
#include<string.h>

int main(){
    char message[14];
    int counter;

    strcpy(message, "Hello, world!");

    printf("How much: ");
    scanf("%d", &counter);

    for(int i = 0; i < counter; i++){
        printf("%3d - %s\n", i, message);
    }

    return 0;
}