#include <stdio.h>
#include <math.h>
#include "source/forge.h"
#include "source/imagine.h"
#include "source/betray.h"
#include "source/relinquish.h"
#include "source/seduce.h"

#define SEDUCE_T_SIZE 0.007        /* default text size */
#define SEDUCE_T_SPACE 0.2         /* default letter spacing */
#define SEDUCE_T_LINE_SPACEING 2.5 /* default line spacing */

void seduce_tutorial_side_panel(BInputState *input, RMatrix *matrix)
{
    static float window_pos[3] = {0, 0, 0};
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
    }
    seduce_manipulator_point_axis(input, matrix, window_pos, window_pos, NULL, FALSE, 0, 1);
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