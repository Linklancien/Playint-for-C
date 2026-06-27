#include "../core/playint_core.h"

/* playint context */

/* Initialize the playint Context, `todolist_cap` is expected to be at least 1 */
void *playint_glfw_glue_Context_init(void *userpointer, unsigned int todolist_cap, unsigned int mode_len);

/* todolist */

/* add an input for the given `mode_id` */
void playint_glfw_glue_Context_mode_todo_add(void *context, int KEY_pressed, unsigned int mode_id);
/* add an input for the current mode` */
void playint_glfw_glue_Context_mode_current_todo_add(void *context, int KEY_pressed);
