#include <stdio.h>
#include <math.h>
#include "source/forge.h"
#include "source/imagine.h"
#include "source/betray.h"
#include "source/relinquish.h"
#include "source/seduce.h"

char *seduce_sample_text = "The legendary former hitman Tarou Sakamoto has thwarted numerous assassins after an enormous bounty on his head was issued. But he cannot seem to catch a break and simply take it easy with his beloved family. A mysterious and infamous figure known as Slur has brought a group of insane death row inmates to Japan, who hold back from nothing to eliminate their targets. Sakamoto is not the only target—the criminals have been assigned to kill various other people, including the new hires at Sakamoto's convenience store, Shin Asakura and Lu Shaotang. The situation escalates even further when the Order, a group of the most skilled Japanese assassins, becomes involved. As the inmates begin wreaking havoc, Sakamoto and his allies must remain vigilant for the sake of everything they hold dear.";

#define SEDUCE_T_SIZE 0.007        /* default text size */
#define SEDUCE_T_SPACE 0.2         /* default letter spacing */
#define SEDUCE_T_LINE_SPACEING 2.5 /* default line spacing */

void seduce_tutorial_side_panel(BInputState *input, RMatrix *matrix)
{
    static float window_pos[3] = {0, 1, 0}, a[3] = {0, -1, 0}, b[3] = {0, 1, 0};
    static char text[256] = {'A', 'B', 'C', 0};
    STextBlockMode modes;
    uint text_end;
    double aspect;

    aspect = betray_screen_mode_get(NULL, NULL, NULL);
    if (input->mode == BAM_DRAW)
    {
        SeduceBackgroundObject *obj;
        obj = seduce_background_object_allocate();

        seduce_background_square_add(obj, NULL, 0,
                                     -1, -aspect, 0,
                                     window_pos[0] + 1.0, aspect * 2.0,
                                     0.2, 0.6, 1.0, 1.0);

        seduce_primitive_surface_draw(input, obj, 1.0);
        seduce_primitive_background_object_free(obj);
        a[0] = b[0] = window_pos[0];
        seduce_element_add_line(input, window_pos, 0, a, b, 0.1); /* Adds a line segment shaped element. */
    }

    seduce_text_edit_line(input, text, NULL, text, 256, -0.9, aspect - SEDUCE_T_SIZE * 3 * 10, window_pos[0] + 0.8, SEDUCE_T_SIZE * 10, "Put text here", TRUE, NULL, NULL, 0.7, 0.7, 0.7, 1.0, 1.0, 1.0, 1.0, 1.0);

    modes.character_position = 0;            /* the first character in the text for this STextBlockMode to be applied to*/
    modes.font = seduce_font_default_get();  /* Font */
    modes.red = 0.8;                         /* Red color component of text */
    modes.green = 0.8;                       /* Green color component of text */
    modes.blue = 0.8;                        /* Blue color component of text */
    modes.alpha = 1.0;                       /* Alpha component of text */
    modes.letter_size = SEDUCE_T_SIZE * 3.0; /* Size of characters */
    modes.letter_spacing = SEDUCE_T_SPACE;   /* Added spacing between characters. Useful for non-monospaced fonts. */

    text_end = seduce_text_block_draw(-0.9, aspect - SEDUCE_T_SIZE * 6 * 10, window_pos[0] + 0.8, 0.5, SEDUCE_T_LINE_SPACEING, SEDUCE_TBAS_STRETCH, seduce_sample_text, 0, &modes, 1);
    seduce_text_block_draw(window_pos[0] + 0.1, aspect - SEDUCE_T_SIZE * 6 * 10, 0.8 - window_pos[0], 0.5, SEDUCE_T_LINE_SPACEING, SEDUCE_TBAS_STRETCH, seduce_sample_text, text_end, &modes, 1);
    seduce_manipulator_point_axis(input, matrix, window_pos, window_pos, NULL, FALSE, 0, 0);
}

void seduce_tutorial_main_loop_func(BInputState *input, void *user_pointer)
{
    uint x_size, y_size;
    RMatrix matrix;
    double aspect;
    float f;
    char *string;

    aspect = betray_screen_mode_get(&x_size, &y_size, NULL);
    if (input->mode == BAM_DRAW)
    {
        r_matrix_identity(&matrix);
        r_matrix_frustum(&matrix, -0.01, 0.01, -0.01 * aspect, 0.01 * aspect, 0.01, 100.0);
        r_matrix_translate(&matrix, 0, 0, -1);
        r_framebuffer_clear(0.0, 0.0, 0.0, 0.0, TRUE, TRUE);
        r_matrix_set(&matrix);
        r_viewport(0, 0, x_size, y_size);
        string = seduce_translate("Hello World");
        f = seduce_text_line_length(NULL, SEDUCE_T_SIZE * 10.0, SEDUCE_T_SPACE, string, ~0);
        seduce_text_line_draw(NULL, f * -0.5, 0, SEDUCE_T_SIZE * 10.0, SEDUCE_T_SPACE, string, 1, 1, 1, 1, ~0);
    }

    if (input->mode == BAM_EVENT)
        if (betray_button_get(-1, BETRAY_BUTTON_F10))
            exit(0);
    seduce_tutorial_side_panel(input, &matrix);

    string = seduce_translate("Exit");

    if (seduce_text_button(input, string, 1.0, SEDUCE_T_SIZE - aspect, 1, SEDUCE_T_SIZE * 3.0, SEDUCE_T_SPACE, string, 1, 1, 1, 1, 1, 0, 0, 1))
        exit(0);

    if (input->mode == BAM_DRAW)
        r_matrix_set(NULL);
    seduce_element_endframe(input, TRUE);
}

int main(int argc, char **argv)
{
    uint x_size, y_size;
    imagine_settings_load("seduce_tutorial.txt");  /* loads all settings from a file */
    seduce_translate_load("seduce_translate.txt"); /* load a translation file */
    printf("main: calling betray_init...\n");
    betray_init(
        B_CT_OPENGL, argc, argv,
        imagine_setting_integer_get("SCREEN_RES_X", 640, "This value represents the window_width"),
        imagine_setting_integer_get("SCREEN_RES_Y", 480, "This value represents the window_height"),
        4, FALSE, seduce_translate("Seduce Tutorial"));
    printf("main: betray_init done\n");
    printf("main: calling r_init...\n");
    r_init(betray_gl_proc_address_get());
    seduce_init();
    betray_action_func_set(seduce_tutorial_main_loop_func,
                           NULL); /* set a function pointer that will be the main loop of the app*/
    printf("main: launching main loop\n");
    betray_launch_main_loop(); /* Start the main loop */
    betray_screen_mode_get(
        &x_size, &y_size,
        NULL); /* Get the current screen size, and if it is in fullscreen. Any pameters can be set
                  to NULL, if you are not interested in any parameter. The fuinction returns the
                  aspect ratio of the window/display*/
    imagine_setting_integer_set("SCREEN_RES_X", x_size, "This value represents the window_width");
    imagine_setting_integer_set("SCREEN_RES_Y", y_size, "This value represents the window_height");
    imagine_settings_save("seduce_tutorial.txt");  /* saves all settings to a file */
    seduce_translate_save("seduce_translate.txt"); /* save a translation file */

    return TRUE;
}