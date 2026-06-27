#include "../../core/playint_core.h"
#include "../../glfw_glue/playint_glfw_glue_core copy.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int i;
}App;

void add(void *app_ptr){
    App *app;
    app = (App *)(app_ptr);

    printf("old: %i new: %i \n",app->i, app->i+1);
    app->i +=1;
}

void sub(void *app_ptr){
    App *app;
    app = (App *)(app_ptr);

    printf("old: %i new: %i \n",app->i, app->i-1);
    app->i -=1;
}


int main(){
    App *app;
    void *playint_context;

    unsigned int keyslinks_len;
    unsigned int todolist_cap;
    unsigned int mode_len;

    unsigned int add_id;
    unsigned int sub_id;

    keyslinks_len = 2;
    todolist_cap = 2;
    mode_len = 2;
    
    app = malloc(sizeof( *app)*1),

    playint_context = playint_Context_init(app, keyslinks_len, todolist_cap, mode_len);
    add_id = playint_Context_function_add(playint_context, "add", add);
    sub_id = playint_Context_function_add(playint_context, "sub", sub);
    
    playint_Context_set_keybinding_by_id(playint_context, add_id);
    playint_Context_mode_todo_add(playint_context, 0, 0);
    playint_Context_set_keybinding_by_id(playint_context, sub_id);
    playint_Context_mode_todo_add(playint_context, 0, 1);
    
    playint_Context_mode_todo_add(playint_context, 0, 1);
    playint_Context_mode_todo_add(playint_context, 0, 0);
    
    playint_Context_mode_set(playint_context, 0);
    playint_Context_mode_current_todo_add(playint_context, 0);
    playint_Context_mode_current_todo_add(playint_context, 0);
    playint_Context_mode_set(playint_context, 1);
    playint_Context_mode_current_todo_add(playint_context, 0);
    playint_Context_mode_current_todo_add(playint_context, 0);
    playint_Context_mode_set(playint_context, 0);
    playint_Context_mode_current_todo_add(playint_context, 0);
    playint_Context_mode_current_todo_add(playint_context, 0);
    
    playint_Context_todo_do_all(playint_context);
}
