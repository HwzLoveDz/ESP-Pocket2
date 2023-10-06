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

volatile char s_cDataUpdate = 0;

jy901b_data_t jy901b_data;

/*Define a message ID*/
#define MSG_INC 1
#define MSG_DEC 2
#define MSG_SET 3
#define MSG_UPDATE 4
#define MSG_UPDATE_REQUEST 5

lv_obj_t *time_label;
lv_obj_t *date_label;
lv_obj_t *after_dot_label;
lv_obj_t *before_dot_label;

lv_obj_t *chart;
lv_obj_t *x_label;
lv_obj_t *y_label;
lv_obj_t *z_label;
lv_chart_cursor_t *cursor;
lv_chart_series_t *chartx;
lv_chart_series_t *charty;
lv_chart_series_t *chartz;

static void uart_chart_timer_cb(lv_timer_t *timer);
static void timer_cb(lv_timer_t *timer);
static void value_handler(void *s, lv_msg_t *m);
static void btn_event_cb(lv_event_t *e);
static void label_event_cb(lv_event_t *e);
static void slider_event_cb(lv_event_t *e);
static void draw_part_event_cb(lv_event_t *e);
static void batInfo_timer_cb(lv_timer_t *timer);
static void uart_dropdown_event_handler(lv_event_t *e);
// static void ta_event_cb(lv_event_t * e);
/**
 * Show how an increment button, a decrement button, as slider can set a value
 * and a label display it.
 * The current value (i.e. the system's state) is stored only in one static variable in a function
 * and no global variables are required.
 */
void my_lv_example_msg_1(void)
{

    lv_msg_subsribe(MSG_INC, value_handler, NULL);
    lv_msg_subsribe(MSG_DEC, value_handler, NULL);
    lv_msg_subsribe(MSG_SET, value_handler, NULL);
    lv_msg_subsribe(MSG_UPDATE, value_handler, NULL);
    lv_msg_subsribe(MSG_UPDATE_REQUEST, value_handler, NULL);

    /*Create a Tab view object*/
    lv_obj_t *tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 50);
    // lv_obj_set_style_bg_color(tabview, lv_color_hex(0x31596a), LV_PART_MAIN);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "USB");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "LRA");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "RTC");
    lv_obj_t *tab4 = lv_tabview_add_tab(tabview, "IMU");
    lv_obj_t *tab5 = lv_tabview_add_tab(tabview, "PMU");

    /*Add content to the tabs*/
    /*tab1*/
    lv_obj_t *label = lv_label_create(tab1);
    lv_label_set_text(label, "USB Virtual Serial AT Test: BG96");

    static lv_obj_t *uart_text = lv_textarea_create(tab1);
    lv_obj_set_size(uart_text, LV_PCT(60), LV_PCT(24));
    lv_obj_align(uart_text, LV_ALIGN_CENTER, 0, 0);

    /*tab2*/
    label = lv_label_create(tab2);
    lv_label_set_text(label, "Touch-Vibrates Test: DRV2605");
    lv_obj_t *panel = lv_obj_create(tab2);
    lv_obj_set_size(panel, LCD_WIDTH * 5 / 6, LV_SIZE_CONTENT);
    lv_obj_center(panel);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_t *btn;
    /*Up button*/
    btn = lv_btn_create(panel);
    lv_obj_set_flex_grow(btn, 1);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_LEFT);
    lv_obj_center(label);
    /*Current value*/
    label = lv_label_create(panel);
    lv_obj_set_flex_grow(label, 2);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(label, "?");
    lv_msg_subsribe_obj(MSG_UPDATE, label, NULL);
    lv_obj_add_event_cb(label, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
    /*Down button*/
    btn = lv_btn_create(panel);
    lv_obj_set_flex_grow(btn, 1);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_RIGHT);
    lv_obj_center(label);
    /*IMG*/
    LV_IMG_DECLARE(img_bulb_gif);
    lv_obj_t *img;
    img = lv_gif_create(panel);
    lv_gif_set_src(img, &img_bulb_gif);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    /*Slider*/
    LV_IMG_DECLARE(img_skew_strip);
    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_img_src(&style_indic, &img_skew_strip);
    lv_style_set_bg_img_tiled(&style_indic, true);
    lv_style_set_bg_img_opa(&style_indic, LV_OPA_30);
    static lv_style_t style_indic_pr;
    lv_style_init(&style_indic_pr);
    lv_style_set_shadow_color(&style_indic_pr, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_shadow_width(&style_indic_pr, 10);
    lv_style_set_shadow_spread(&style_indic_pr, 3);
    lv_obj_t *slider = lv_slider_create(panel);
    lv_obj_add_style(slider, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_style(slider, &style_indic_pr, LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_obj_set_flex_grow(slider, 1);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_ALL, NULL);
    lv_msg_subsribe_obj(MSG_UPDATE, slider, NULL);

    /* As there are new UI elements that don't know the system's state
     * send an UPDATE REQUEST message which will trigger an UPDATE message with the current value*/
    lv_msg_send(MSG_UPDATE_REQUEST, NULL);

    /*tab3*/
    label = lv_label_create(tab3);
    lv_label_set_text(label, "Real-Time Clock Test: BM8563");

    /*Create a time label, set its text and align it to the center*/
    time_label = lv_label_create(tab3);
    lv_timer_create(timer_cb, 1000, NULL);          // 每1秒钟更新一次label的显示
    lv_obj_set_width(time_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(time_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(time_label, 0);
    lv_obj_set_y(time_label, 25);
    lv_obj_set_align(time_label, LV_ALIGN_TOP_MID);
    lv_label_set_text_fmt(time_label, "00:00"); // 初始文本
    lv_obj_set_style_text_color(time_label, lv_color_hex(0x2980b9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(time_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(time_label, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Create a date label, set its text and align it to the center*/
    date_label = lv_label_create(tab3);
    lv_obj_set_x(date_label, 0);
    lv_obj_set_y(date_label, 86);
    lv_obj_set_align(date_label, LV_ALIGN_TOP_MID);
    lv_label_set_text_fmt(date_label, "Jan 01 Sun"); // 初始文本
    lv_obj_set_style_text_color(date_label, lv_color_hex(0x2980b9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(date_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(date_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

/*tab4*/
    label = lv_label_create(tab4);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(label, "Inertial-Measurement-Unit: JY901B");

    panel = lv_obj_create(tab4);
    lv_obj_set_size(panel, 290, 40);
    lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_set_style_bg_color(panel, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(panel, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF); // 禁止滚动条
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);        // 清除可滚动标志
    lv_obj_t *uart_dropdown = lv_dropdown_create(panel);
    // lv_dropdown_set_text(uart_dropdown, "JY901B MODE");
    lv_obj_set_size(uart_dropdown, 140, 36);
    lv_obj_align(uart_dropdown, LV_ALIGN_LEFT_MID, -10, 0);
    lv_dropdown_set_dir(uart_dropdown, LV_DIR_RIGHT);
    lv_dropdown_set_options(uart_dropdown, "JY901B-ACC\nJY901B-GYRO\nJY901B_ANGLE\nJY901B-MAG");
    lv_obj_set_style_text_align(uart_dropdown, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_add_event_cb(uart_dropdown, uart_dropdown_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t *chart_panel = lv_obj_create(tab4);
    lv_obj_set_size(chart_panel, LCD_WIDTH - 30, LCD_HEIGHT * 2 / 3);
    lv_obj_align(chart_panel, LV_ALIGN_CENTER, 0, 60);
    lv_obj_set_style_bg_color(chart_panel, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(chart_panel, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(chart_panel, LV_SCROLLBAR_MODE_OFF); // 禁止滚动条
    lv_obj_clear_flag(chart_panel, LV_OBJ_FLAG_SCROLLABLE);        // 清除可滚动标志
    /*
        LV_PART_MAIN：可以用来修改背景和栅格线的样式。参考3.1
        LV_PART_SCROLLBAR：当放大的时候，会绘制ScrollBar。参考3.2
        LV_PART_ITEMS：对应series画的线或柱状图。参考3.3
        LV_PART_INDICATOR：对应ITEMS上的点。参考3.4
        LV_PART_CURSOR：对应光标。参考3.5
        LV_PART_TICKS：对应记号和标签。参考3.6
    */
    chart = lv_chart_create(chart_panel);
    lv_timer_create(uart_chart_timer_cb, 100, NULL); // 每0.1秒钟更新一次 chart 的显示

    lv_obj_set_size(chart, LCD_WIDTH - 30 - 45, LCD_HEIGHT * 2 / 3 - 10);
    lv_obj_set_style_width(chart, 0, LV_PART_INDICATOR); // 图表标点大小
    lv_obj_set_style_height(chart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_color(chart, lv_color_hex(0xdcdcdc), LV_PART_MAIN); // 图表格栅颜色
    lv_obj_set_style_border_color(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN);  // 图表边框颜色
    lv_obj_set_style_bg_color(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_SCROLLBAR); // 滚动条颜色
    // lv_obj_set_style_bg_color(chart, lv_palette_main(LV_PALETTE_BLUE_GREY), LV_PART_MAIN);    // 图表背景颜色
    lv_obj_align(chart, LV_ALIGN_CENTER, 17, 0);

    lv_chart_set_point_count(chart, 200);                                         // 设置为200个点显示
    lv_chart_set_div_line_count(chart, 5, 10);                                    // 设施栅格数
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 5, 3, 5, 3, true, 40); // 设置记号和标签
    // lv_obj_set_style_line_color(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_TICKS);   // 设置记号颜色
    lv_obj_set_style_text_color(chart, lv_palette_main(LV_PALETTE_BLUE_GREY), LV_PART_TICKS);  // 设置标签颜色

    lv_chart_set_zoom_x(chart, 256 * 1); // x缩放.256表示原大小
    lv_chart_set_zoom_y(chart, 256 * 1); // y缩放.256表示原大小

    // cursor = lv_chart_add_cursor(chart, lv_palette_main(LV_PALETTE_GREEN), LV_DIR_ALL);   // 添加光标
    // lv_obj_set_style_width(chart, 5, LV_PART_CURSOR);   // 设置光标点的大小
    // lv_obj_set_style_height(chart, 5, LV_PART_CURSOR);  // 设置光标点的大小
    // lv_point_t point = {50, 50};
    // lv_chart_set_cursor_pos(chart, cursor, &point); // 设置光标相对于 chart 的坐标（不会随着滚动条变化）

    chartx = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    charty = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    chartz = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);

    // lv_chart_set_next_value(chart, ser1, 200);
    // static const lv_coord_t value[] = { 0, 100, 300, 0, 100, 300, 0, 100, 300, 0};
    // lv_chart_set_ext_y_array(chart, chartSer1, (lv_coord_t*)value);

    x_label = lv_label_create(chart);
    lv_obj_align(x_label, LV_ALIGN_TOP_LEFT, 168, 0);
    lv_label_set_text(x_label, "X: 0.00");
    lv_obj_set_style_text_color(x_label, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(x_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    y_label = lv_label_create(chart);
    lv_obj_align(y_label, LV_ALIGN_TOP_LEFT, 168, 15);
    lv_label_set_text(y_label, "Y: 0.00");
    lv_obj_set_style_text_color(y_label, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(y_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    z_label = lv_label_create(chart);
    lv_obj_align(z_label, LV_ALIGN_TOP_LEFT, 168, 30);
    lv_label_set_text(z_label, "Z: 0.00");
    lv_obj_set_style_text_color(z_label, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(z_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

/*tab5*/
    label = lv_label_create(tab5);
    lv_label_set_text(label, "Power-Management: AXP202");
    lv_timer_create(batInfo_timer_cb, 1000, NULL); // 每1秒钟更新一次label的显示

    panel = lv_obj_create(tab5);
    lv_obj_set_x(panel, -10);
    lv_obj_set_y(panel, 12);
    lv_obj_set_align(panel, LV_ALIGN_RIGHT_MID);
    lv_obj_set_width(panel, 180);                            /// 1
    lv_obj_set_height(panel, 120);                           /// 1
    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF); // 禁止滚动条
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);        // 清除可滚动标志

    cb1 = lv_checkbox_create(panel);
    lv_obj_set_x(cb1, 0);
    lv_obj_set_y(cb1, 0);
    lv_obj_set_align(cb1, LV_ALIGN_TOP_LEFT);
    lv_obj_add_state(cb1, LV_STATE_DEFAULT);
    lv_checkbox_set_text(cb1, "Play animation");
    lv_obj_add_event_cb(cb1, ui_sw_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *cb2;
    cb2 = lv_checkbox_create(panel);
    lv_obj_set_x(cb2, 0);
    lv_obj_set_y(cb2, 28);
    lv_obj_set_align(cb2, LV_ALIGN_TOP_LEFT);
    lv_obj_add_state(cb2, LV_STATE_DEFAULT);
    lv_checkbox_set_text(cb2, "Charge state");

    lv_obj_t *batPerPanel;
    batPerPanel = lv_obj_create(panel);
    lv_obj_set_x(batPerPanel, 0);
    lv_obj_set_y(batPerPanel, 8);
    lv_obj_set_width(batPerPanel, 164); /// 1
    lv_obj_set_height(batPerPanel, 44); /// 1
    lv_obj_set_align(batPerPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_scrollbar_mode(batPerPanel, LV_SCROLLBAR_MODE_OFF); // 禁止滚动条
    lv_obj_clear_flag(batPerPanel, LV_OBJ_FLAG_SCROLLABLE);        // 清除可滚动标志

    before_dot_label = lv_label_create(batPerPanel);
    lv_obj_set_x(before_dot_label, -52);
    lv_obj_set_y(before_dot_label, 0);
    lv_obj_set_align(before_dot_label, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(before_dot_label, "00");
    lv_obj_set_style_text_color(before_dot_label, lv_color_hex(0x31a231), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(before_dot_label, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    after_dot_label = lv_label_create(batPerPanel);
    lv_obj_set_x(after_dot_label, 82);
    lv_obj_set_y(after_dot_label, 10);
    lv_obj_set_align(after_dot_label, LV_ALIGN_LEFT_MID);
    lv_label_set_text(after_dot_label, ".00%");
    lv_obj_set_style_text_color(after_dot_label, lv_color_hex(0x31a231), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(after_dot_label, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_init(tab5);

    // 将指定的 label 对象滚动到可见区域，使用带有动画效果的方式
    lv_obj_scroll_to_view_recursive(time_label, LV_ANIM_ON);
}

static void value_handler(void *s, lv_msg_t *m)
{
    LV_UNUSED(s);

    static int32_t value = 100;
    int32_t old_value = value;
    switch (lv_msg_get_id(m))
    {
    case MSG_INC:
        if (value < 100)
            value++;
        break;
    case MSG_DEC:
        if (value > 0)
            value--;
        break;
    case MSG_SET:
    {
        const int32_t *new_value = reinterpret_cast<const int32_t *>(lv_msg_get_payload(m));
        // const int32_t * new_value = lv_msg_get_payload(m);
        value = *new_value;
    }
    break;
    case MSG_UPDATE_REQUEST:
        lv_msg_send(MSG_UPDATE, &value);
        break;
    default:
        break;
    }

    if (value != old_value)
    {
        lv_msg_send(MSG_UPDATE, &value);
        lcd_bk_pwm_set(value); // ^ 更改屏幕背光
        xTaskNotifyGive(xTouchVibrates); // ^ 值更改时震动

    }
}

static void btn_event_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
    {
        if (lv_obj_get_index(btn) == 0)
        { /*First object is the dec. button*/
            lv_msg_send(MSG_DEC, NULL);
        }
        else
        {
            lv_msg_send(MSG_INC, NULL);
        }
    }
}

static void label_event_cb(lv_event_t *e)
{
    lv_obj_t *label = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_MSG_RECEIVED)
    {
        lv_msg_t *m = lv_event_get_msg(e);
        if (lv_msg_get_id(m) == MSG_UPDATE)
        {
            const int32_t *v = reinterpret_cast<const int32_t *>(lv_msg_get_payload(m));
            // const int32_t * v = lv_msg_get_payload(m);
            lv_label_set_text_fmt(label, "%ld %%", *v);
        }
    }
}

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        int32_t v = lv_slider_get_value(slider);
        lv_msg_send(MSG_SET, &v);
    }
    else if (code == LV_EVENT_MSG_RECEIVED)
    {
        lv_msg_t *m = lv_event_get_msg(e);
        if (lv_msg_get_id(m) == MSG_UPDATE)
        {
            const int32_t *v = reinterpret_cast<const int32_t *>(lv_msg_get_payload(m));
            // const int32_t * v = lv_msg_get_payload(m);
            lv_slider_set_value(slider, *v, LV_ANIM_OFF);
        }
    }
}

static void timer_cb(lv_timer_t *timer)
{
    // 获取时间
    create_RTC_update_func();
    // 格式化时间字符串
    char time_buf[20];
    sprintf(time_buf, "%02d:%02d",
            timeStruct.Hours, timeStruct.Minutes); //, timeStruct.Seconds
    // 格式化日期字符串
    char date_buf[20];
    static const char *month_names[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    static const char *weekday_names[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    sprintf(date_buf, "%s %02d %s",
            weekday_names[dateStruct.WeekDay], dateStruct.Date, month_names[dateStruct.Month]);
    // 更新label的显示文本
    lv_label_set_text(time_label, time_buf);
    lv_label_set_text(date_label, date_buf);
}

static void batInfo_timer_cb(lv_timer_t *timer)
{
    // 获取电量百分比
    float batt_percentage = create_PMU_getBatPercentage_func();
    if (batt_percentage >= 100.00)
        batt_percentage = 100.00;
    int before_dot = (int)batt_percentage;                       // 小数点前的数字
    int after_dot = (int)((batt_percentage - before_dot) * 100); // 小数点后的数字
    // 格式化字符串
    char before_dot_buf[6];
    sprintf(before_dot_buf, "%d", before_dot);
    char after_dot_buf[10];
    sprintf(after_dot_buf, ".%02d%%", after_dot);
    // 更新label的显示文本
    lv_label_set_text(before_dot_label, before_dot_buf);
    lv_label_set_text(after_dot_label, after_dot_buf);
}

static void uart_chart_timer_cb(lv_timer_t *timer)
{

    static float fAcc[3], fGyro[3], fAngle[3];
    static int i;
    // static unsigned long int x_time = 0;
    static float y_x = 0.0;
    static float y_y = 0.0;
    static float y_z = 0.0;

    if (s_cDataUpdate)
    {
        for (i = 0; i < 3; i++)
        {
            fAcc[i] = sReg[AX + i] / 32768.0f * 16.0f;
            fGyro[i] = sReg[GX + i] / 32768.0f * 2000.0f;
            fAngle[i] = sReg[Roll + i] / 32768.0f * 180.0f;
        }
        if ((s_cDataUpdate & ACC_UPDATE) && (jy901b_data == JY901B_ACC))
        {
            // printf("acc:%.3f %.3f %.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
            s_cDataUpdate &= ~ACC_UPDATE;
            y_x = fAcc[0];
            y_y = fAcc[1];
            y_z = fAcc[2];
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -2, 2);  // 设置加速度测量范围 ACC
        }
        if ((s_cDataUpdate & GYRO_UPDATE) && (jy901b_data == JY901B_GYRO))
        {
            // printf("gyro:%.3f %.3f %.3f\r\n", fGyro[0], fGyro[1], fGyro[2]);
            s_cDataUpdate &= ~GYRO_UPDATE;
            y_x = fGyro[0];
            y_y = fGyro[1];
            y_z = fGyro[2];
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -500, 500);  // 设置角加速度测量范围 GYRO
        }
        if ((s_cDataUpdate & ANGLE_UPDATE) && (jy901b_data == JY901B_ANGLE))
        {
            // printf("angle:%.3f %.3f %.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
            s_cDataUpdate &= ~ANGLE_UPDATE;
            y_x = fAngle[0];
            y_y = fAngle[1];
            y_z = fAngle[2];
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -180, 180); // 设置角度测量范围 ANGLE
        }
        if ((s_cDataUpdate & MAG_UPDATE) && (jy901b_data == JY901B_MAG))
        {
            // printf("mag:%d %d %d\r\n", sReg[HX], sReg[HY], sReg[HZ]);
            s_cDataUpdate &= ~MAG_UPDATE;
            y_x = sReg[HX]; //
            y_y = sReg[HY]; //
            y_z = sReg[HZ]; //
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -10000, 10000); // 设置磁力计测量范围 MAG
        }
    }
    lv_chart_set_next_value(chart, chartx, y_x);
    lv_chart_set_next_value(chart, charty, y_y);
    lv_chart_set_next_value(chart, chartz, y_z);
    /* X轴图例 */
    char x_label_buf[10];
    sprintf(x_label_buf, "X: %.2f", y_x);
    lv_label_set_text(x_label, x_label_buf);
    /* Y轴图例 */
    char y_label_buf[10];
    sprintf(y_label_buf, "Y: %.2f", y_y);
    lv_label_set_text(y_label, y_label_buf);
    /* Z轴图例 */
    char z_label_buf[10];
    sprintf(z_label_buf, "Z: %.2f", y_z);
    lv_label_set_text(z_label, z_label_buf);
    /* X轴时间轴加1 */
    // x_time += 1;
}

static void uart_dropdown_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        // char buf[32];
        // lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        /* JY901B-ACC JY901B-GYRO JY901B_ANGLE JY901B-MAG */
        switch (lv_dropdown_get_selected(obj))
        {
        case JY901B_ACC:
            /* code */ jy901b_data = JY901B_ACC;
            break;
        case JY901B_GYRO:
            /* code */ jy901b_data = JY901B_GYRO;
            break;
        case JY901B_ANGLE:
            /* code */ jy901b_data = JY901B_ANGLE;
            break;
        case JY901B_MAG:
            /* code */ jy901b_data = JY901B_MAG;
            break;
        default:
            break;
        }
    }
}

// void my_lv_example_usb_1(void)
// {
//     lv_obj_t * dropdown = lv_dropdown_create(lv_scr_act());
//     lv_dropdown_set_text(dropdown, "Port");
//     lv_obj_set_size(dropdown, LV_PCT(20), 36);
//     lv_obj_align(dropdown, LV_ALIGN_TOP_RIGHT, -80, 10);
//     lv_dropdown_set_options(dropdown, "Serial-AT\nSerial-GNSS");
//     // lv_dropdown_add_option(dropdown, "Insert1", 1);

//     lv_obj_t * send_btn = lv_btn_create(lv_scr_act());
//     lv_obj_set_size(send_btn, LV_PCT(20), 34);
//     lv_obj_align(send_btn, LV_ALIGN_TOP_RIGHT, -10, 11);
//     lv_obj_set_style_shadow_ofs_x(send_btn, 0, LV_PART_MAIN);
//     lv_obj_set_style_shadow_ofs_y(send_btn, 0, LV_PART_MAIN);
//     lv_obj_t * send_label = lv_label_create(send_btn);
//     lv_label_set_text(send_label, "Send");
//     lv_obj_set_size(send_label, LV_PCT(100), LV_PCT(100));
//     lv_obj_align(send_label, LV_ALIGN_CENTER, 0, 1);

//     lv_obj_t * usb_panel = lv_obj_create(lv_scr_act());
//     lv_obj_set_size(usb_panel, LV_PCT(94), 170);
//     lv_obj_align(usb_panel, LV_ALIGN_TOP_MID, 0, 54);
//     lv_obj_t * receive_label = lv_label_create(usb_panel);
//     lv_label_set_text(receive_label, "Receive Area");
//     lv_obj_align(receive_label, LV_ALIGN_TOP_LEFT, 0, 0);

//     /*Create a keyboard to use it with an of the text areas*/
//     lv_obj_t * kb = lv_keyboard_create(lv_scr_act());
//     lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);    // 初始隐藏键盘
//     /*Create a text area. The keyboard will write here*/
//     lv_obj_t * ta;
//     ta = lv_textarea_create(lv_scr_act());
//     lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, 10);
//     lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
//     lv_textarea_set_placeholder_text(ta, "Input Command...");
//     lv_obj_set_size(ta, LV_PCT(50), 36);
//     lv_keyboard_set_textarea(kb, ta);
// }

// static void ta_event_cb(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * ta = lv_event_get_target(e);
//     lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e);
//     if(code == LV_EVENT_FOCUSED) {
//         lv_keyboard_set_textarea(kb, ta);
//         lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     }

//     if(code == LV_EVENT_DEFOCUSED) {
//         lv_keyboard_set_textarea(kb, NULL);
//         lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     }
// }

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
    my_lv_example_msg_1();
    // my_lv_example_chart_1();
    // my_lv_example_usb_1();
    // ui_init();   /* use squarline */
}
