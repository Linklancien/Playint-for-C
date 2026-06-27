#include "../core/playint_core.h"
#include <stdio.h>

/* playint context */

/* Initialize the playint Context, `todolist_cap` is expected to be at least 1 */
void *playint_glfw_glue_Context_init(void *userpointer, unsigned int todolist_cap, unsigned int mode_len){
    unsigned int keyslinks_len = 300;
    return playint_Context_init(userpointer, keyslinks_len, todolist_cap, mode_len);
}

/* todolist */

/* from a KEY return the corresponding index */
unsigned int glfw_convert_KEY_macro_to_index(unsigned int KEY_pressed){
    unsigned int index = -1;
    
    /* repartition: */
    /* ------------ */
    /*
     * | 32      |                | 0       |
     * | 39      |                | 1       |
     * | 44/57   | 57-44 = 13     | 2/15    |
     * | 59      |                | 16      |
     * | 61      |                | 17      |
     * | 65/93   | 93-65 = 28     | 18/46   |
     * | 96      |                | 47      |
     * | 161     |                | 48      |
     * | 162     |                | 49      |
     * | 256/284 | 284 - 256 = 28 | 50/78   |
     * | 290/314 | 314 - 290 = 24 | 79/103  |
     * | 320/336 | 336 - 320 = 16 | 104/120 |
     * | 340/348 | 348 - 340 = 8  | 121/129 |
     */
    if (KEY_pressed ==  32){
        index = 0;
    }
    else if (KEY_pressed ==  39){
        index = 1;
    }
    else if (KEY_pressed ==  59){
        index = 16;
    }
    else if (KEY_pressed ==  61){
        index = 17;
    }
    else if (KEY_pressed == 96){
        index = 47;
    }
    else if (KEY_pressed == 161){
        index = 48;
    }
    else if (KEY_pressed == 162){
        index = 48;
    }
    else if (KEY_pressed > 340){
        index = index - 340 + 121;
    }
    else if (KEY_pressed > 320){
        index = index - 320 + 104;
    }
    else if (KEY_pressed > 290){
        index = index - 290 + 79;
    }
    else if (KEY_pressed > 256){
        index = index - 256 + 50;
    }
    else if (KEY_pressed > 65){
        index = index - 65 + 18;
    }
    else if (KEY_pressed > 44){
        index = index - 44 + 2;
    }
    
    if (index < 0){
        printf("error with index: %i", index);
    }
    return index;
}

/* add an input for the given `mode_id` */
void playint_glfw_glue_Context_mode_todo_add(void *context, unsigned int KEY_pressed, unsigned int mode_id){
    playint_Context_mode_todo_add(context, glfw_convert_KEY_macro_to_index(KEY_pressed), mode_id);
}

/* add an input for the current mode` */
void playint_glfw_glue_Context_mode_current_todo_add(void *context, unsigned int KEY_pressed){
    playint_Context_mode_current_todo_add(context, glfw_convert_KEY_macro_to_index(KEY_pressed));
}
