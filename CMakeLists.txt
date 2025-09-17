# Minimal CMake configuration for building the Seduce tutorial on Windows with MSVC
cmake_minimum_required(VERSION 3.10)

# Project definition
project(seduce_tutorial C)

# Require C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Include headers from the local source tree (Quel Solaar libs live in source/)
include_directories(${PROJECT_SOURCE_DIR}/source)

# Collect all C sources from the Quel Solaar libraries recursively
# Use CONFIGURE_DEPENDS to re-glob upon CMake reconfigure when files are added/removed
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    # "${PROJECT_SOURCE_DIR}/source/*.c"
    "${PROJECT_SOURCE_DIR}/source/b_keys.h"
    "${PROJECT_SOURCE_DIR}/source/b_main.c"
    "${PROJECT_SOURCE_DIR}/source/b_win32_key_codes.c"
    "${PROJECT_SOURCE_DIR}/source/b_win32_main.c"
    "${PROJECT_SOURCE_DIR}/source/betray.h"

    "${PROJECT_SOURCE_DIR}/source/f_math.c"
    "${PROJECT_SOURCE_DIR}/source/f_matrix_make.c"
    "${PROJECT_SOURCE_DIR}/source/f_matrix_operations.c"
    "${PROJECT_SOURCE_DIR}/source/f_mem_debug.c"
    "${PROJECT_SOURCE_DIR}/source/f_noise.c"
    "${PROJECT_SOURCE_DIR}/source/f_path.c"
    "${PROJECT_SOURCE_DIR}/source/f_sort.c"
    "${PROJECT_SOURCE_DIR}/source/f_text.c"
    "${PROJECT_SOURCE_DIR}/source/f_utf8.c"
    "${PROJECT_SOURCE_DIR}/source/f_types.c"
    "${PROJECT_SOURCE_DIR}/source/forge.h"

    "${PROJECT_SOURCE_DIR}/source/i_dir.c"
    "${PROJECT_SOURCE_DIR}/source/i_library.c"
    "${PROJECT_SOURCE_DIR}/source/i_settings.c"
    "${PROJECT_SOURCE_DIR}/source/i_shared_memory.c"
    "${PROJECT_SOURCE_DIR}/source/i_threads.c"
    "${PROJECT_SOURCE_DIR}/source/i_time.c"
    "${PROJECT_SOURCE_DIR}/source/imagine.h"

    "${PROJECT_SOURCE_DIR}/source/r_draw_buffer.c"
    "${PROJECT_SOURCE_DIR}/source/r_draw_extensions.c"
    "${PROJECT_SOURCE_DIR}/source/r_draw_framebuffer.c"
    "${PROJECT_SOURCE_DIR}/source/r_draw_parser.c"
    "${PROJECT_SOURCE_DIR}/source/r_draw_primitive.c"
    "${PROJECT_SOURCE_DIR}/source/r_draw_shader.c"
    "${PROJECT_SOURCE_DIR}/source/r_draw_state.c"
    "${PROJECT_SOURCE_DIR}/source/r_draw_uniform.c"
    "${PROJECT_SOURCE_DIR}/source/r_include.h"
    "${PROJECT_SOURCE_DIR}/source/r_matrix.c"
    "${PROJECT_SOURCE_DIR}/source/relinquish.h"

    "${PROJECT_SOURCE_DIR}/source/s_background.c"
    "${PROJECT_SOURCE_DIR}/source/s_background_old.c"
    "${PROJECT_SOURCE_DIR}/source/s_draw.c"
    "${PROJECT_SOURCE_DIR}/source/s_draw_3d.c"
    "${PROJECT_SOURCE_DIR}/source/s_draw_3d.h"
    "${PROJECT_SOURCE_DIR}/source/s_draw_3d_data.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_abel.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_arial.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_eurasia.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_impact.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_lane.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_lato.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_luke.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_oswald.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_sansumi.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_times.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_verdana.c"
    "${PROJECT_SOURCE_DIR}/source/s_font_verdana2.c"
    "${PROJECT_SOURCE_DIR}/source/s_lens.c"
    "${PROJECT_SOURCE_DIR}/source/s_lines.c"
    "${PROJECT_SOURCE_DIR}/source/s_main.c"
    "${PROJECT_SOURCE_DIR}/source/s_manipulator_point.c"
    "${PROJECT_SOURCE_DIR}/source/s_manipulator_rotate.c"
    "${PROJECT_SOURCE_DIR}/source/s_manipulator_scale.c"
    "${PROJECT_SOURCE_DIR}/source/s_manipulator_space.c"
    "${PROJECT_SOURCE_DIR}/source/s_particles.c"
    "${PROJECT_SOURCE_DIR}/source/s_popup.c"
    "${PROJECT_SOURCE_DIR}/source/s_popup_detect.c"
    "${PROJECT_SOURCE_DIR}/source/s_projection.c"
    "${PROJECT_SOURCE_DIR}/source/s_select.c"
    "${PROJECT_SOURCE_DIR}/source/s_settings_window.c"
    "${PROJECT_SOURCE_DIR}/source/s_settings_window2.c"
    # "${PROJECT_SOURCE_DIR}/source/s_shape_edit.c"
    "${PROJECT_SOURCE_DIR}/source/s_sort.c"
    "${PROJECT_SOURCE_DIR}/source/s_text.c"
    "${PROJECT_SOURCE_DIR}/source/s_text.h"
    "${PROJECT_SOURCE_DIR}/source/s_text_edit.c"
    "${PROJECT_SOURCE_DIR}/source/s_text_exporter.c"
    "${PROJECT_SOURCE_DIR}/source/s_text_file_format.c"
    "${PROJECT_SOURCE_DIR}/source/s_text_output.c"
    "${PROJECT_SOURCE_DIR}/source/s_text_output.h"
    "${PROJECT_SOURCE_DIR}/source/s_text_widget.c"
    "${PROJECT_SOURCE_DIR}/source/s_texture.c"
    "${PROJECT_SOURCE_DIR}/source/s_widget.c"
    # Corrected filename: radial (not radical)
    "${PROJECT_SOURCE_DIR}/source/s_widget_radial.c"
    # Add translation module providing seduce_translate / seduce_translate_save
    "${PROJECT_SOURCE_DIR}/source/s_translate.c"
    "${PROJECT_SOURCE_DIR}/source/s_widget_visualizer.c"
    "${PROJECT_SOURCE_DIR}/source/seduce.h"
 
)

# Filter out sources that conflict with this app's entry point or other platforms/tests
# - Exclude any file that defines a separate entry point (e.g., *_main.c, win32_main.c)
# - Exclude Android glue and android-specific/test programs
# - Exclude standalone demo/test programs that also contain a main()
# if(SOURCES)
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)android_native_app_glue\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/).*android.*\\.c$")
#     # Keep core Betray files; don't exclude platform main loops here
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/).*test.*\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)g_main2\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)d_main\\.c$")
#     # Drop editor/demo/persuade subsystems not required for the tutorial
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)(seduce_editor_.*|confuse_.*|confuce_.*|la_.*|p2_.*|vs_.*)\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)seduce_persuade\\.c$")
#     # Exclude Betray plugin system (depends on headers/assets not present/needed for tutorial)
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)betray_plugin_.*\\.c$")
#     # Exclude gather/ffmpeg plugins (depend on external FFmpeg SDK not available here)
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)gather_.*\\.c$")
#     # Exclude character/editor pipelines (c_*.c) not needed for a window+render tutorial
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)c_.*\\.c$")
#     # Exclude legacy/old modules that require missing GL extension plumbing
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)s_draw_buffer_old\\.c$")
#     # Exclude specific legacy/alt implementations pulling missing headers
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)c_primitives_old\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)c_limb2(_old)?\\.c$")
#     # Exclude utility memory test/alt entry
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)k_memory\\.c$")
#     # Exclude any stray double-suffixed files
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/).+\\.c\\.c$")
#     # Explicitly exclude known standalone programs in the tree that define main()
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)v_encryption\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)v_prime\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)v_bignum\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)v_cmd_gen\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)s_translate\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)imgine_test\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)seduce_manipulator_demo\\.c$")
#     # Exclude entire Seduce UI subsystem for minimal tutorial (not required by main.c)
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)s_.*\\.c$")
#     # Exclude plugin API glue (we're not loading plugins)
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)[bg]_plugin_api\\.c$")
#     # Exclude Verse networking, Keep DB, and Testify systems
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)v_.*\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)k_.*\\.c$")
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)t_.*\\.c$")
#     # Exclude Enough (e_*.c) storage/network layers that require Verse
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)e_.*\\.c$")
#     # Exclude DocGen standalone tool
#     list(FILTER SOURCES EXCLUDE REGEX ".*(^|/)DocGen\\.c$")
# endif()

# Define the executable with our app entry point and the filtered Quel Solaar sources
add_executable(seduce_tutorial
    ${PROJECT_SOURCE_DIR}/main.c
    ${SOURCES}
)

# Target include dirs (duplicate of global include for clarity/scoping)
target_include_directories(seduce_tutorial PRIVATE ${PROJECT_SOURCE_DIR}/source)

# Windows-specific compile options and definitions
if(MSVC)
    target_compile_options(seduce_tutorial PRIVATE /W3 /permissive-)
    target_compile_definitions(seduce_tutorial PRIVATE _CRT_SECURE_NO_WARNINGS WIN32_LEAN_AND_MEAN _USE_MATH_DEFINES)
endif()

# Link against required Windows system libraries for OpenGL and Win32
target_link_libraries(seduce_tutorial PRIVATE
    opengl32
    user32
    gdi32
    winmm
    shell32
    advapi32
    ws2_32
    comdlg32
)

# Optionally set output directories to be under the build tree (Visual Studio will place Debug/Release subdirs)
set_target_properties(seduce_tutorial PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)
