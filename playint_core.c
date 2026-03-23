#include <stdlib.h>
typedef void(*playint_UserFunction)(void) ;

typedef struct{
    char *name;
    playint_UserFunction *function_pointer_list;
}playint_Actions;

enum Type{
    activated,
    change,
    count,
};

typedef struct {
    enum Type type;
    unsigned int id;
}Interaction;

typedef struct {
	Interaction *listpointer; /* state/id */
	unsigned int idstart;
	unsigned int idend;
	unsigned int cap;
}TodoList;

typedef struct{
    void *userpointer; /* the pointer used to call the user functions */
    enum Type state;
    playint_Actions *actions;
    unsigned int actions_len;
    unsigned int *keyslinks;
    unsigned int keyslinks_len;
    TodoList todolist;
}playint_Context;

/* playint context */

void* playint_Context_init(void *userpointer, unsigned int keyslinks_len, unsigned int todolist_cap){
    playint_Context* context;
    unsigned int* keyslinks;

    keyslinks = malloc((sizeof *keyslinks)*keyslinks_len);

    context->userpointer = userpointer;
    context->keyslinks = keyslinks;
    context->todolist.cap = todolist_cap;

    return context;
};

void *playint_Context_init_from(char *path);
void playint_Context_set_from(void *context, char *path);
void playint_Context_save_to(void *context, char *path);

void playint_Context_free(playint_Context *context){
    free(context->userpointer);
    free(context->actions);
    free(context->keyslinks);
    free(context->todolist.listpointer);
    free(context);
};


void playint_Context_change_userpointer(playint_Context *context, void *userpointer){
    context->userpointer=userpointer;
}

/* actions */

void playint_Context_action_add(void *context, char *name, playint_UserFunction function_pointer);
unsigned int playint_Context_action_get_by_id(void *context, unsigned int id);
unsigned int *playint_Context_action_get_by_name(void *context, char *name);

/* keyslinks */

void playint_Context_keyslinks_set(playint_Context *context, unsigned int keyslinks_len){
    context->keyslinks = realloc(context->keyslinks, keyslinks_len);
};

void playint_Context_keyslinks_change_at(void *context, unsigned int id);
void playint_Context_keyslinks_change_all(void *context);
unsigned int playint_Context_keyslinks_get_by_id(void *context, unsigned int id);
unsigned int *playint_Context_keyslinks_get_by_linked_id(void *context, unsigned int linked_id);
unsigned int *playint_Context_keyslinks_get_by_linked_name(void *context, char *linked_name);

/* todolist */

void playint_Context_todolist_add(playint_Context *context, int id_pressed){
    unsigned int old_cap;
    unsigned int i;

    if (context->todolist.idstart != context->todolist.idend){
        if (context->todolist.idend + 1 == context->todolist.cap){
            context->todolist.cap *= 2;
            context->todolist.listpointer = realloc(context->todolist.listpointer, context->todolist.cap);
            context->todolist.idend += 1;
        }
        else if (context->todolist.idend + 1 == context->todolist.idstart){
            old_cap = context->todolist.cap;
            context->todolist.cap *= 2;
            context->todolist.listpointer = realloc(context->todolist.listpointer, context->todolist.cap);
            /* change the place of the elements between 0 and idend to old_cap and old_cap + idend */
            for (i = 0; i < context->todolist.idend; i++){
                context->todolist.listpointer[i+old_cap] = context->todolist.listpointer[i] ;
            }
            context->todolist.idend += old_cap + 1;
        }
        else{
            context->todolist.idend += 1;
        }
    }

    context->todolist.listpointer[context->todolist.idend].type = context->state;
    context->todolist.listpointer[context->todolist.idend].id = id_pressed;
};

void playint_Context_todolist_do_one(void *context);
void playint_Context_todolist_do_all(void *context);
