#include "playint_core.c"

/* playint context */

void *playint_Context_init(void *userpointer, unsigned int keyslinks_len, unsigned int todolist_cap);
void *playint_Context_init_from(char *path);
void playint_Context_set_from(void *context, char *path);
void playint_Context_save_to(void *context, char *path);
void playint_Context_free(void *context);
void playint_Context_change_userpointer(void *context, void *userpointer);

/* actions */

void playint_Context_action_add(void *context, char *name, playint_UserFunction function_pointer);
unsigned int playint_Context_action_get_by_id(void *context, unsigned int id);
unsigned int *playint_Context_action_get_by_name(void *context, char *name);

/* keyslinks */

void playint_Context_keyslinks_set(void *context, unsigned int keyslinks_len);
void playint_Context_keyslinks_change_at(void *context, unsigned int id);
void playint_Context_keyslinks_change_all(void *context);
unsigned int playint_Context_keyslinks_get_by_id(void *context, unsigned int id);
unsigned int *playint_Context_keyslinks_get_by_linked_id(void *context, unsigned int linked_id);
unsigned int *playint_Context_keyslinks_get_by_linked_name(void *context, char *linked_name);

/* todolist */

void playint_Context_todolist_add(void *context, int id_pressed);
void playint_Context_todolist_do_one(void *context);
void playint_Context_todolist_do_all(void *context);
