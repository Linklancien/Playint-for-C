typedef void(*playint_UserFunction)(void*) ;

/* playint context */

/* Initialize the playint Context, `todolist_cap` is expected to be at least 1 */
void *playint_Context_init(void *userpointer, unsigned int keyslinks_len, unsigned int todolist_cap, unsigned int mode_len);
/* not implemented yet */
void *playint_Context_init_from(char *path);
/* not implemented yet */
void playint_Context_set_from(void *context, char *path);
/* not implemented yet */
void playint_Context_save_to(void *context, char *path);
/* free all playint allocation linked to a given context */
void playint_Context_free(void *context);
/* return the len of the keybindings */
unsigned int playint_Context_keybinding_get(void *context);
/* set a new len for the keybindings */
void playint_Context_keybinding_set(void *context, unsigned int new_keybinding);
/* set a new user point which is used by the actions to `userpointer` */
void playint_Context_change_userpointer(void *context, void *userpointer);

/* functions */

/* add a function with a given `name`, it returns the index */
unsigned int playint_Context_function_add(void *context, char *name, playint_UserFunction function_pointer);
/* returns the name of the function at the given `id` */
char *playint_Context_function_get_name_by_id(void *context, unsigned int id);
/* returns an array of the ids of the function that have a given name, the first element at [0] the len of the array */
unsigned int *playint_Context_function_get_id_by_name(void *context, char *name);
/* set the current keybinding value to the given id */
void playint_Context_set_keybinding_by_id(void *context, unsigned int id_function_to_link);
/* set the current keybinding value to id of the first function that have the given name */
void playint_Context_set_keybinding_by_name(void *context, char *name);

/* mode */

/* returns the id of the running mode */
unsigned int playint_Context_mode_get(void *context);
/* set the id of the running mode to the given `new_mode` */
void playint_Context_mode_set(void *context, unsigned int new_mode);
/* returns the len of the `mode_array` */
unsigned int playint_Context_mode_get_len(void *context);
/* returns the len of the mode array */
void playint_Context_mode_set_len(void *context, unsigned int new_len);

/* keyslinks */

/* returns the number of keys linked */
unsigned int playint_Context_keyslinks_len_get(void *context);
/* set the new number of keys linked */
void playint_Context_keyslinks_len_set(void *context, unsigned int new_number_of_keys);
/* return the id of the function linked at `keyslinks_id` for the mode `mode_id` */
unsigned int playint_Context_mode_keyslinks_get_linked_by_id(void *context, int mode_id, unsigned int keyslinks_id);
/* the first element is the length, returns an array of the id  */
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_id(void *context, int mode_id, unsigned int linked_id);
/* the first element is the length */
unsigned int *playint_Context_mode_keyslinks_get_id_by_linked_name(void *context, int mode_id, char *linked_name);

unsigned int playint_Context_mode_current_keyslinks_get_linked_by_id(void *context, unsigned int keyslinks_id);
/* the first element is the length */
unsigned int *playint_Context_mode_current_keyslinks_get_id_by_linked_id(void *context, unsigned int linked_id);
/* the first element is the length */
unsigned int *playint_Context_mode_current_keyslinks_get_id_by_linked_name(void *context, char *linked_name);

/* todolist */

/* returns the len of the todo array */
unsigned int playint_Context_todo_get_len(void *context);
/* add an input for the given `mode_id` */
void playint_Context_mode_todo_add(void *context, unsigned int id_pressed, unsigned int mode_id);
/* add an input for the current mode` */
void playint_Context_mode_current_todo_add(void *context, unsigned int id_pressed);
/* execute the first input recorded */
void playint_Context_todo_do_one(void *context);
/* execute all the input recorded in chronological order */
void playint_Context_todo_do_all(void *context);
/* execute all the input recorded in chronological order and then resize the todo array to the given `new_cap`, it should be at least 1 */
void playint_Context_todo_do_all_and_set_cap(void *context, unsigned int new_cap);
