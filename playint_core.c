#include <stdlib.h>
typedef void(*playint_UserFunction)(void*) ;

typedef struct{
    char *name;
    playint_UserFunction function_pointer_list;
}playint_Actions;

enum playint_InteractionType{
    activated,
    changed,
    count,
};

typedef struct {
    enum playint_InteractionType type;
    unsigned int id_pressed;
}playint_Interaction;

typedef struct {
	playint_Interaction *list_interaction; /* state/id */
	unsigned int *list_new_actions_linked;
	unsigned int idstart;
	unsigned int idnext;
	unsigned int cap;
}playint_TodoList;

typedef struct{
    void *userpointer; /* the pointer used to call the user functions */
    enum playint_InteractionType state;
    playint_Actions *actions;
    unsigned int actions_len;
    unsigned int new_action;
    unsigned int *keyslinks;
    unsigned int keyslinks_len;
    playint_TodoList todolist;
}playint_Context;

/* playint context */

void* playint_Context_init(void *userpointer, unsigned int keyslinks_len, unsigned int todolist_cap){
    playint_Context *context;
    unsigned int *keyslinks;
    playint_Interaction *list_interaction;
    unsigned int *list_new_actions_linked;

    keyslinks = malloc((sizeof *keyslinks)*keyslinks_len);
    list_interaction = malloc((sizeof *list_interaction)*todolist_cap);
    list_new_actions_linked = malloc((sizeof *list_new_actions_linked)*todolist_cap);

    context->userpointer = userpointer;
    context->keyslinks = keyslinks;
    context->todolist.list_interaction = list_interaction;
    context->todolist.list_new_actions_linked = list_new_actions_linked;
    context->todolist.cap = todolist_cap;

    return context;
}

void *playint_Context_init_from(char *path);
void playint_Context_set_from(void *context, char *path);
void playint_Context_save_to(void *context, char *path);

void playint_Context_free(playint_Context *context){
    free(context->userpointer);
    free(context->actions);
    free(context->keyslinks);
    free(context->todolist.list_interaction);
    free(context);
}


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
}

void playint_Context_keyslinks_change_at(void *context, unsigned int id);
void playint_Context_keyslinks_change_all(void *context);
unsigned int playint_Context_keyslinks_get_by_id(void *context, unsigned int id);
unsigned int *playint_Context_keyslinks_get_by_linked_id(void *context, unsigned int linked_id);
unsigned int *playint_Context_keyslinks_get_by_linked_name(void *context, char *linked_name);

/* todolist */

void playint_Context_todolist_change_idnext(playint_Context *context){
    unsigned int old_cap;
    unsigned int i;

    if (context->todolist.idnext + 1 == context->todolist.cap){
        context->todolist.cap *= 2;
        context->todolist.list_interaction = realloc(context->todolist.list_interaction, context->todolist.cap);
    }
    else if (context->todolist.idnext + 1 == context->todolist.idstart){
        old_cap = context->todolist.cap;
        context->todolist.cap *= 2;
        context->todolist.list_interaction = realloc(context->todolist.list_interaction, context->todolist.cap);
        /* change the place of the elements between 0 and idnext to old_cap and old_cap + idnext */
        for (i = 0; i < context->todolist.idnext; i++){
            context->todolist.list_interaction[i+old_cap] = context->todolist.list_interaction[i] ;
        }
        context->todolist.idnext += old_cap;
    }
    context->todolist.idnext += 1;
}

unsigned int playint_Context_todolist_get_len(playint_Context *context){
    unsigned int len;
    if (context->todolist.idstart <= context->todolist.idnext){
        len = context->todolist.idnext - context->todolist.idstart;
    }
    else{
        len = context->todolist.cap - context->todolist.idnext + context->todolist.idstart;
    }
    return len;
}

void playint_Context_todolist_add(playint_Context *context, int id_pressed){
    context->todolist.list_interaction[context->todolist.idnext].type = context->state;
    context->todolist.list_interaction[context->todolist.idnext].id_pressed = id_pressed;
    if (context->state == changed){
        context->todolist.list_new_actions_linked[context->todolist.idnext] = context->new_action;
    }

    playint_Context_todolist_change_idnext(context);
}

void playint_Context_todolist_do_one(playint_Context *context){
    playint_Interaction interaction;
    unsigned int id_action;
    if (context->todolist.idstart != context->todolist.idnext){
        interaction = context->todolist.list_interaction[context->todolist.idstart];
        context->todolist.idstart += 1;

        if (interaction.type == activated){
            id_action = context->keyslinks[interaction.id_pressed];
            context->actions[id_action].function_pointer_list(context->userpointer);
        }
        else if (interaction.type == changed){

        }
    }
}

void playint_Context_todolist_do_all(playint_Context *context){
    unsigned int i;

    if (context->todolist.idstart < context->todolist.idnext){
        for (i = context->todolist.idstart; i < context->todolist.idnext ; i++){
        }
    }
    else{
        for (i = context->todolist.idstart; i < context->todolist.cap ; i++){}
        for (i = 0; i < context->todolist.idnext ; i++){}
    }

    context->todolist.idstart = 0;
    context->todolist.idnext = 1;
}
