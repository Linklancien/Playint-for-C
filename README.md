# Presentation
This project aims to ease the use of keybindings by providing a dependance-free module that allow, multiples bindings modes, a to control of when the function linked to the key activate, a possibility to change the bindings during the execution
# Example:
```c
#include "[path to]playint/core/playint_core.h"
#include <stdio.h>

typedef struct{
    int test_value;
}App ;

void add_fn(void *test){
    App *app;
    app = (App*)test;
    printf("In add, App.value ");
    printf("was %i ",app->test_value);
    app->test_value += 1;
    printf("it is now %i\n",app->test_value);
    fflush(stdout);
}

void sub_fn(void *test){
    App *app;
    app = (App*)test;
    printf("In sub, App.value ");
    printf("was %i ",app->test_value);
    app->test_value -= 1;
    printf("it is now %i\n",app->test_value);
    fflush(stdout);
}

int main(){
    void *playint_context_ptr;
    unsigned int keyslinks_len;
    unsigned int todolist_cap;
    unsigned int mode_len;
    App app;

    keyslinks_len = 2;
    todolist_cap = 1;
    mode_len = 2;

    printf("START \n");
    fflush(stdout);
    playint_context_ptr = playint_Context_init(&app, keyslinks_len, todolist_cap, mode_len);
    printf("END context INIT \n");
    fflush(stdout);


    playint_Context_function_add(playint_context_ptr, "Test add", add_fn);
    playint_Context_function_add(playint_context_ptr, "Test sub", sub_fn);

    printf("END fn INIT \n");
    fflush(stdout);

    playint_Context_mode_set(playint_context_ptr, 0);
    playint_Context_set_keybinding_by_id(playint_context_ptr, 0);
    playint_Context_mode_current_todo_add(playint_context_ptr, 0);

    playint_Context_mode_set(playint_context_ptr, 1);
    playint_Context_set_keybinding_by_id(playint_context_ptr, 1);
    playint_Context_mode_current_todo_add(playint_context_ptr, 0);
    printf("END links INIT \n");
    fflush(stdout);

    playint_Context_mode_todo_add(playint_context_ptr, 0, 0);
    playint_Context_mode_set(playint_context_ptr, 0);
    playint_Context_mode_current_todo_add(playint_context_ptr, 0);
    playint_Context_mode_current_todo_add(playint_context_ptr, 0);

    playint_Context_mode_todo_add(playint_context_ptr, 0, 1);
    playint_Context_mode_set(playint_context_ptr, 1);
    playint_Context_mode_todo_add(playint_context_ptr, 0, 1);
    playint_Context_mode_current_todo_add(playint_context_ptr, 0);

    printf("START TODO \n");
    fflush(stdout);
    playint_Context_todo_do_all(playint_context_ptr);
    printf("END \n");
    fflush(stdout);

    return 0;
}

```
