#include <stdio.h>
#include <stdlib.h>
typedef void(*playint_UserFunction)(void*) ;

typedef struct{
    char *name;
    playint_UserFunction function_pointer_list;
}playint_Function;

enum playint_InteractionType{
    activated,
    changed,
    count
};

typedef struct {
    enum playint_InteractionType type;
    unsigned int id_pressed;
}playint_Interaction;

typedef struct {
	playint_Interaction *interaction_array; /* state/id */
	unsigned int *new_function_linked_array;
	unsigned int idstart;
	unsigned int idnext;
	unsigned long cap;
}playint_TodoList;

typedef struct{
    unsigned int *keyslinks_array;
}playint_Mode;

typedef struct{
    void *userpointer; /* the pointer used to call the user functions */

    playint_Function *function_array;
    unsigned int function_array_len;

    playint_Mode *mode_array;
    unsigned int mode_array_len;
    unsigned int number_of_keys;
    unsigned int current_mode;

    unsigned int keybinding;

    playint_TodoList todolist;
}playint_Context;

/* playint context */

void *playint_Context_init(void *userpointer, unsigned int keyslinks_len, unsigned int todolist_cap, unsigned int mode_len){
    unsigned int *new_function_linked_array;
    playint_Context *context;
    playint_Interaction *interaction_array;
    playint_Mode *mode_array;

    context = malloc((sizeof( *context)*1));
    context->number_of_keys = keyslinks_len;

    mode_array = malloc((sizeof *mode_array)*mode_len);
    interaction_array = malloc((sizeof *interaction_array)*todolist_cap);
    new_function_linked_array = malloc((sizeof *new_function_linked_array)*todolist_cap);

    context->userpointer = userpointer;
    context->mode_array = mode_array;
    context->mode_array_len = mode_len;
    context->todolist.interaction_array = interaction_array;
    context->todolist.new_function_linked_array = new_function_linked_array;
    context->todolist.cap = todolist_cap;

    return context;
}

void *playint_Context_init_from(char *path);
void playint_Context_set_from(playint_Context *context, char *path);
void playint_Context_save_to(playint_Context *context, char *path);

void playint_Context_free(playint_Context *context){
    unsigned int i;
    for (i = 0; i < context->mode_array_len; i++){
        free(context->mode_array[i].keyslinks_array);
    }

    free(context->mode_array);
    free(context->userpointer);
    free(context->function_array);
    free(context->todolist.interaction_array);
    free(context);
}

unsigned int playint_Context_keybinding_get(playint_Context *context){
    return context->keybinding;
}

void playint_Context_keybinding_set(playint_Context *context, unsigned int new_keybinding){
    context->keybinding = new_keybinding;
}

void playint_Context_change_userpointer(playint_Context *context, void *userpointer){
    context->userpointer=userpointer;
}

/* function */

void playint_Context_action_add(playint_Context *context, char *name, playint_UserFunction function_pointer){
    context->function_array = realloc(context->function_array, sizeof(*context->function_array)*context->function_array_len);
    context->function_array[context->function_array_len].name = name;
    context->function_array[context->function_array_len].function_pointer_list = function_pointer;
    context->function_array_len += 1;
}

char *playint_Context_action_get_name_by_id(playint_Context *context, unsigned int id){
    if (context->function_array_len <=id){
        return 0;
    }
    return context->function_array[id].name;
}

unsigned int *playint_Context_action_get_id_by_name(playint_Context *context, char *name){
    unsigned int i;
    unsigned int current_id;
    unsigned int *ids;

    for (i=0; i < context->function_array_len ; i ++ ){
        if (context->function_array[i].name == name){
            current_id += 1;
            ids = realloc(ids, current_id);
            ids[current_id] = i;
        }
    }

    return ids;
}

void playint_Context_change_keybinding_by_id(playint_Context *context, unsigned int id_keybinding){
    context->keybinding = id_keybinding;
}

void playint_Context_change_keybinding_by_name(playint_Context *context, char *name){
    context->keybinding = playint_Context_action_get_id_by_name(context, name)[0];
}

/* keyslinks */

unsigned int playint_Context_number_of_keys_get(playint_Context *context){
    return context->number_of_keys ;
}
void playint_Context_number_of_keys_set(playint_Context *context, unsigned int new_number_of_keys){
    unsigned int i;
    for (i = 0; i < context->mode_array_len; i++){
        context->mode_array[i].keyslinks_array = realloc(context->mode_array[i].keyslinks_array, new_number_of_keys);
    }
    context->number_of_keys = new_number_of_keys;
}

unsigned int playint_Context_mode_keyslinks_get_linked_by_id(playint_Context *context, int mode_id, unsigned int keyslinks_id){
    return context->mode_array[mode_id].keyslinks_array[keyslinks_id];
}
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_id(playint_Context *context, int mode_id, unsigned int linked_id);
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_name(playint_Context *context, int mode_id, char *linked_name);

unsigned int playint_Context_current_mode_keyslinks_get_linked_by_id(playint_Context *context, unsigned int keyslinks_id){
    return playint_Context_mode_keyslinks_get_linked_by_id(context, context->current_mode, keyslinks_id);
}

unsigned int *playint_Context_current_mode_keyslinks_get_id_by_linked_id(playint_Context *context, unsigned int linked_id){
    return playint_Context_mode_keyslinks_get_id_by_linked_id(context, context->current_mode, linked_id);
}

unsigned int *playint_Context_current_mode_keyslinks_get_id_by_linked_name(playint_Context *context, char *linked_name){
    return playint_Context_mode_keyslinks_get_id_by_linked_name(context, context->current_mode, linked_name);
}


/* todolist */

/* local */
void playint_Context_todoarray_change_idnext(playint_Context *context){
    unsigned long old_cap;
    unsigned int i;

    if (context->todolist.idnext + 1 == context->todolist.cap){
        context->todolist.cap *= 2 ;

        context->todolist.new_function_linked_array = realloc(context->todolist.new_function_linked_array, (sizeof *context->todolist.new_function_linked_array)*context->todolist.cap);
        context->todolist.interaction_array = realloc(context->todolist.interaction_array, (sizeof *context->todolist.interaction_array)*context->todolist.cap);
    }
    else if (context->todolist.idnext + 1 == context->todolist.idstart){
        old_cap = context->todolist.cap;
        context->todolist.cap *= 2;
        context->todolist.new_function_linked_array = realloc(context->todolist.new_function_linked_array, (sizeof *context->todolist.new_function_linked_array)*context->todolist.cap);
        context->todolist.interaction_array = realloc(context->todolist.interaction_array, (sizeof *context->todolist.interaction_array)*context->todolist.cap);
        /* change the place of the elements between 0 and idnext to old_cap and old_cap + idnext */
        for (i = 0; i < context->todolist.idnext; i++){
            context->todolist.interaction_array[i+old_cap] = context->todolist.interaction_array[i] ;
            context->todolist.new_function_linked_array[i+old_cap] = context->todolist.new_function_linked_array[i] ;
        }
        context->todolist.idnext += old_cap;
    }
    context->todolist.idnext += 1;
}

unsigned int playint_Context_todoarray_get_len(playint_Context *context){
    unsigned int len;
    if (context->todolist.idstart <= context->todolist.idnext){
        len = context->todolist.idnext - context->todolist.idstart;
    }
    else{
        len = context->todolist.cap - context->todolist.idnext + context->todolist.idstart;
    }
    return len;
}

void playint_Context_todoarray_add(playint_Context *context, int id_pressed){
    context->todolist.interaction_array[context->todolist.idnext].type = context->state;
    context->todolist.interaction_array[context->todolist.idnext].id_pressed = id_pressed;
    if (context->state == changed){
        context->todolist.new_function_linked_array[context->todolist.idnext] = context->keybinding;
    }

    playint_Context_todoarray_change_idnext(context);
}

void playint_Context_todoarray_do_one(playint_Context *context){
    playint_Interaction interaction;
    unsigned int id_action;

    if (context->todolist.idstart != context->todolist.idnext){
        interaction = context->todolist.interaction_array[context->todolist.idstart];

        if (interaction.type == activated){
            id_action = context->keyslinks[interaction.id_pressed];
            context->function_array[id_action].function_pointer_list(context->userpointer);
        }
        else if (interaction.type == changed){
            playint_Context_mode_keyslinks_change_at(context, int mode_id, interaction.id_pressed, context->todolist.new_function_linked_array[context->todolist.idstart]);
        }
        context->todolist.idstart += 1;
    }
}

void playint_Context_todoarray_do_all(playint_Context *context){
    playint_Interaction interaction;
    unsigned int id_action;
    unsigned int i;

    if (context->todolist.idstart < context->todolist.idnext){
        for (i = context->todolist.idstart; i < context->todolist.idnext ; i++){
            interaction = context->todolist.interaction_array[i];

            if (interaction.type == activated){
                id_action = context->keyslinks[interaction.id_pressed];
                context->function_array[id_action].function_pointer_list(context->userpointer);
            }
            else if (interaction.type == changed){
                playint_Context_mode_keyslinks_change_at(context, int mode_id, interaction.id_pressed, context->todolist.new_function_linked_array[i]);
            }
        }
    }
    else{
        for (i = context->todolist.idstart; i < context->todolist.cap ; i++){
            interaction = context->todolist.interaction_array[i];

            if (interaction.type == activated){
                id_action = context->keyslinks[interaction.id_pressed];
                context->function_array[id_action].function_pointer_list(context->userpointer);
            }
            else if (interaction.type == changed){
                playint_Context_mode_keyslinks_change_at(context, int mode_id, interaction.id_pressed, context->todolist.new_function_linked_array[i]);
            }
        }
        for (i = 0; i < context->todolist.idnext ; i++){
            interaction = context->todolist.interaction_array[i];

            if (interaction.type == activated){
                id_action = context->keyslinks[interaction.id_pressed];
                context->function_array[id_action].function_pointer_list(context->userpointer);
            }
            else if (interaction.type == changed){
                playint_Context_mode_keyslinks_change_at(context, int mode_id, interaction.id_pressed, context->todolist.new_function_linked_array[i]);
            }
        }
    }

    context->todolist.idstart = 0;
    context->todolist.idnext = 0;
}
