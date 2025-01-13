#include<stdio.h>

int function_one(){
    printf("That's first func");
    return 1;
}

int function_two(){
    printf("That's second func");
    return 2;
}

void func_call(int (*func) ()){
    int (*function_ptr) ();
    function_ptr = func;
    printf("Func adress: %p\n", function_ptr);
    int value = func();
    printf("Value of func: %d\n", value);
}

int main(){

    printf("First function:\n");
    func_call(*function_one);
    printf("Second function:\n");
    func_call(*function_two);

    return 0;
}