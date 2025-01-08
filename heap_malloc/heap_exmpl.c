#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void ifMallocTrue(void *var_ptr){
    if(var_ptr == NULL){
        fprintf(stderr, "Fault, the memory from heap cant be malloc\n");
        exit(-1);
    }
}

int main(int argc, char *argv[]) {

    char *char_ptr;
    int *int_ptr;
    int memory_size;

    if(argc < 2){
        memory_size = 50;

    } else {
        memory_size = atoi(argv[1]);
    }

    printf("\t[+] malloc %d bytes from heap for variable char_ptr\n", memory_size);
    char_ptr = (char *) malloc(memory_size);

    ifMallocTrue(char_ptr);

    strcpy(char_ptr, "This memory are located in heap\n");
    printf("char_ptr %p -> %s\n", char_ptr, char_ptr);

    printf("\t[+] malloc 12 bytes from heap to variable int_ptr\n");
    int_ptr = (int *) malloc(12);

    ifMallocTrue(int_ptr);

    *int_ptr = 31337;
    printf("int_ptr %p -> %d\n", int_ptr, *int_ptr);

    printf("\t[-]free memory that was malloc for char_ptr\n");
    free(char_ptr);

    printf("\t[+] malloc another 15 bytes from heap to variable char_ptr\n");
    char_ptr = (char *) malloc(15);

    ifMallocTrue(char_ptr);
    strcpy(char_ptr, "new memory\n");

    printf("char_ptr %p -> %s\n", char_ptr, char_ptr);

    printf("\t[-]free memory that was malloc for int_ptr\n");
    free(int_ptr);

    printf("\t[-]free memory tha was malloc for char_ptr\n");
    free(char_ptr);

    return 0;
}