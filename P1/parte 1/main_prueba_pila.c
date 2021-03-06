#include "stack.h"
#include "generic_string.h"

int main(int argc, char** argv) {
    Stack * p_s_string1, * p_s_string2;
    char * aux_string;
    p_s_string1 = (Stack *) stack_ini(destroy_p_string, copy_p_string,
                                      print_p_string);
    p_s_string2 = (Stack *) stack_ini(destroy_p_string, copy_p_string,
                                      print_p_string);

    stack_push(p_s_string1, "hola 1");
    stack_push(p_s_string1, "hola 2");
    stack_push(p_s_string1, "hola 3");
    stack_push(p_s_string1, "hola 4");
    stack_push(p_s_string1, "hola 5");
    stack_push(p_s_string1, "hola 6");
    stack_push(p_s_string1, "hola 7");
    while (!stack_isEmpty(p_s_string1)) {
        aux_string = (char*) stack_pop(p_s_string1);
        stack_push(p_s_string2, aux_string);
        destroy_p_string(aux_string);
    }
    printf("stack 2:\n");
    stack_print(stdout, p_s_string2);
    printf("size of the stack: %d\nis stack2 empty? : %d\nis stack2 full? : %d\n", stack_size(p_s_string2), stack_isEmpty(p_s_string2), stack_isFull(p_s_string2));
    printf("\nstack1: (should not print any element)\n");
    printf("size of the stack: %d\nis stack1 empty? : %d\nis stack1 full? : %d\n", stack_size(p_s_string1), stack_isEmpty(p_s_string1), stack_isFull(p_s_string1));
    stack_destroy(p_s_string2);
    stack_destroy(p_s_string1);
    return 0;
}