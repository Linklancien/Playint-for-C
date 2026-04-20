typedef void(*playint_UserFunction)(void*) ;

/* playint context */

void *playint_Context_init(void *userpointer, unsigned int keyslinks_len, unsigned int todoarray_cap);
void *playint_Context_init_from(char *path);
void playint_Context_set_from(void *context, char *path);
void playint_Context_save_to(void *context, char *path);
void playint_Context_free(void *context);
void playint_Context_change_state_activated(void *context);
void playint_Context_change_state_changed(void *context);
void playint_Context_change_userpointer(void *context, void *userpointer);

/* actions */

void playint_Context_action_add(void *context, char *name, playint_UserFunction function_pointer);
char *playint_Context_action_get_name_by_id(void *context, unsigned int id);
unsigned int *playint_Context_action_get_id_by_name(void *context, char *name);
void playint_Context_change_action_to_link_by_id(void *context, unsigned int id_action_to_link);
void playint_Context_change_action_to_link_by_name(void *context, char *name);

/* mode */
void playint_Context_mode_(void *context);

/* keyslinks */

void playint_Context_mode_keyslinks_len_set(void *context, int mode_id, unsigned int keyslinks_len);
void playint_Context_mode_keyslinks_change_all(void *context, int mode_id);
unsigned int playint_Context_mode_keyslinks_get_linked_by_id(void *context, int mode_id, unsigned int keyslinks_id);
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_id(void *context, int mode_id, unsigned int linked_id);
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_name(void *context, int mode_id, char *linked_name);

/* todolist */

unsigned int playint_Context_todoarray_get_len(void *context);
void playint_Context_todoarray_add(void *context, int id_pressed);
void playint_Context_todoarray_do_one(void *context);
void playint_Context_todoarray_do_all(void *context);
