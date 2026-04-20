typedef void(*playint_UserFunction)(void*) ;

/* playint context */

void *playint_Context_init(void *userpointer, unsigned int keyslinks_len, unsigned int todolist_cap, unsigned int mode_len);
/* not implemented yet */
void *playint_Context_init_from(char *path);
/* not implemented yet */
void playint_Context_set_from(void *context, char *path);
/* not implemented yet */
void playint_Context_save_to(void *context, char *path);
void playint_Context_free(void *context);
bool playint_Context_keybinding_get(void *context);
void playint_Context_keybinding_set(void *context, bool );
void playint_Context_change_userpointer(void *context, void *userpointer);

/* actions */

void playint_Context_action_add(void *context, char *name, playint_UserFunction function_pointer);
char *playint_Context_action_get_name_by_id(void *context, unsigned int id);
unsigned int *playint_Context_action_get_id_by_name(void *context, char *name);
void playint_Context_change_action_to_link_by_id(void *context, unsigned int id_action_to_link);
void playint_Context_change_action_to_link_by_name(void *context, char *name);

/* mode */
unsigned int playint_Context_mode_get(void *context);
void playint_Context_mode_set(void *context, unsigned int new_mode);
unsigned int playint_Context_mode_get_len(void *context);
void playint_Context_mode_set_len(void *context, unsigned int new_len);

/* keyslinks */

unsigned int playint_Context_keyslinks_len_get(void *context);
void playint_Context_keyslinks_len_set(void *context, unsigned int new_number_of_keys);

unsigned int playint_Context_mode_keyslinks_get_linked_by_id(void *context, int mode_id, unsigned int keyslinks_id);
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_id(void *context, int mode_id, unsigned int linked_id);
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_name(void *context, int mode_id, char *linked_name);

unsigned int playint_Context_mode_current_keyslinks_get_linked_by_id(void *context, unsigned int keyslinks_id);
unsigned int *playint_Context_mode_current_keyslinks_get_id_by_linked_id(void *context, unsigned int linked_id);
unsigned int *playint_Context_mode_current_keyslinks_get_id_by_linked_name(void *context, char *linked_name);

/* todolist */

unsigned int playint_Context_todo_get_len(void *context);
void playint_Context_mode_todo_add(void *context, int id_pressed, unsigned int mode_id);
void playint_Context_mode_current_todo_add(void *context, int id_pressed);
void playint_Context_todo_do_one(void *context);
void playint_Context_todo_do_all(void *context);
void playint_Context_todo_do_all_and_set_cap(void *context, unsigned int new_cap);
