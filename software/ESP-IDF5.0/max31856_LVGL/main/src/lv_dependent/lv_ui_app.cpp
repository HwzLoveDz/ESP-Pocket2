/**
 * @file lv_ui_app.cpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief ui & peripheral
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "lv_ui_app.hpp"

/*
 ! 如果在添加额外的 widget 组件或编译时部分 widget 在 link 时出现问题，比如使用某个 widget 依赖例程时报错 undefined,请在 components\lvgl\Kconfig
 ! 文件中添加 components\lvgl\lvgl\examples\widgets 目录中报错的 widget 文件名称.
 */
void create_demo_app(void)
{
    // lv_example_get_started_1();
    // lv_example_get_started_2();
    // lv_example_get_started_3();
    // lv_example_style_1();
    // lv_example_scroll_6();
    // lv_example_led_1();-

    // lv_example_keyboard_1(); //
    // lv_example_win_1();
    // lv_example_table_2();
    // lv_example_meter_4();
    // lv_example_meter_3();
    // lv_example_meter_2();
    // lv_example_list_1(); //
    // lv_example_list_2();
    // lv_example_img_4();
    // lv_example_img_3();
    // lv_example_calendar_1();
    // lv_example_canvas_2();
    // lv_example_canvas_1();
    // lv_example_snapshot_1();
    // lv_example_flex_1();
    // lv_example_anim_timeline_1();
    // lv_example_anim_3();
    // lv_example_gridnav_3();
    // lv_example_msg_2();
    // lv_example_fragment_2();
    // lv_example_roller_3();
    // lv_example_msgbox_1();
    // lv_example_win_1();
    // lv_example_line_1();
    // lv_example_chart_6();
    // lv_example_chart_7();
    // lv_example_menu_3();
    // lv_example_menu_4();
    // lv_example_menu_5();
    // lv_example_table_2();
    // lv_example_tabview_1();
    // lv_example_msg_3();

    // lv_example_gif_1();
    // lv_example_qrcode_1();
    // lv_example_ffmpeg_1();
    // lv_example_ffmpeg_2();

    // my_lv_example_list_1();
    // my_lv_example_chart();
    // my_lv_example_usb_1();
    ui_init();   /* use squarline */
}
