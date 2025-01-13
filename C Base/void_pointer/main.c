#include<stdio.h>

int main(){
    char char_arr[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_arr[5] = {1,2,3,4,5};

    void* void_ptr;

    void_ptr = (void *) char_arr;
    for(int i= 0; i < 5; i++){
        printf("[char pointer] pointing at adress %p, that including symbol '%c'\n", void_ptr, *((char *) void_ptr));
        void_ptr += sizeof(char);
    }

    void_ptr = (void *) int_arr;
    for(int i = 0; i < 5; i++){
        printf("[int pointer] pointing at adress %p, that including number '%d\n'", void_ptr, *((int *)void_ptr));
        void_ptr += sizeof(int);
    }

    return 0;
}
