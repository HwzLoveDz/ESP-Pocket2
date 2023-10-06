// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.2
// LVGL version: 8.3.4
// Project name: Futuristic_Ebike

#include "lv_ui.h"
#include "lv_ui_helpers.h"

/////////////////// VARIABLES ////////////////////
void Particle1_Animation(lv_obj_t * TargetObject, int delay);
void Particle2_Animation(lv_obj_t * TargetObject, int delay);
void Particle3_Animation(lv_obj_t * TargetObject, int delay);
void Fash_Animation(lv_obj_t * TargetObject, int delay);
void Wave1_Animation(lv_obj_t * TargetObject, int delay);
void Wave2_Animation(lv_obj_t * TargetObject, int delay);
void ui_sw_event_cb(lv_event_t * e);
lv_obj_t * ui_Group_Battery_Indicator;
lv_obj_t * ui_Particle_Group;
lv_obj_t * ui_Image_Particle1;
lv_obj_t * ui_Image_Particle2;
lv_obj_t * ui_Image_Particle3;
lv_obj_t * ui_Wave_Group;
lv_obj_t * ui_Wave1;
lv_obj_t * ui_Wave2;
lv_obj_t * ui_Image_Battery_BG;
lv_obj_t * ui_Image_Flash;
lv_obj_t * ui____initial_actions0;
lv_obj_t * cb1;
lv_obj_t * sw;
lv_obj_t * list1;
const lv_img_dsc_t * particle__array[3] = {&ui_img_particle_1_png, &ui_img_particle_2_png, &ui_img_particle_3_png};
const lv_img_dsc_t * water__array[2] = {&ui_img_water_1_png, &ui_img_water_2_png};

void Particle1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 19800);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Particle2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 7920);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void Particle3_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 3960);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void Fash_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 100);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 1200);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Wave1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 7000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 103);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Wave2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 5000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, -103);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
///////////////////// FUNCTIONS ////////////////////
void ui_sw_event_cb(lv_event_t * e)
{
    sw = lv_event_get_target(e);
    if(lv_obj_has_state(sw, LV_STATE_CHECKED))
    {
        Particle1_Animation(ui_Image_Particle1, 0);
        Particle2_Animation(ui_Image_Particle2, 0);
        Particle3_Animation(ui_Image_Particle3, 0);
        Wave1_Animation(ui_Wave1, 0);
        Wave2_Animation(ui_Wave2, 0);
        lv_obj_add_state(sw, LV_STATE_CHECKED | LV_STATE_DISABLED);
    }
    // else if(lv_obj_has_state(sw, LV_STATE_DEFAULT))
    // {
    //     lv_anim_del(ui_Image_Particle1, NULL);
    //     lv_anim_del(ui_Image_Particle2, NULL);
    //     lv_anim_del(ui_Image_Particle3, NULL);
    //     lv_anim_del(ui_Wave1, NULL);
    //     lv_anim_del(ui_Wave2, NULL);
    //     lv_anim_del_all();
    // }
}
///////////////////// SCREENS ////////////////////
void ui_Driving_screen_init(lv_obj_t * ui_Driving)
{
    // ui_Driving = lv_obj_create(NULL);
    // lv_obj_clear_flag(ui_Driving, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Group_Battery_Indicator = lv_obj_create(ui_Driving);
    lv_obj_set_width(ui_Group_Battery_Indicator, 100);
    lv_obj_set_height(ui_Group_Battery_Indicator, lv_pct(115));
    lv_obj_set_x(ui_Group_Battery_Indicator, 0);
    lv_obj_set_y(ui_Group_Battery_Indicator, 10);
    lv_obj_set_align(ui_Group_Battery_Indicator, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_Group_Battery_Indicator, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Group_Battery_Indicator, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Group_Battery_Indicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Particle_Group = lv_obj_create(ui_Group_Battery_Indicator);
    lv_obj_set_width(ui_Particle_Group, 50);
    lv_obj_set_height(ui_Particle_Group, 120);
    lv_obj_set_align(ui_Particle_Group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Particle_Group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Particle_Group, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Particle_Group, lv_color_hex(0x202420), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Particle_Group, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Particle_Group, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image_Particle1 = lv_img_create(ui_Particle_Group);
    lv_img_set_src(ui_Image_Particle1, &ui_img_particle_1_png);
    lv_obj_set_height(ui_Image_Particle1, 240);
    lv_obj_set_width(ui_Image_Particle1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_Image_Particle1, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image_Particle1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image_Particle1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_blend_mode(ui_Image_Particle1, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image_Particle2 = lv_img_create(ui_Particle_Group);
    lv_img_set_src(ui_Image_Particle2, &ui_img_particle_3_png);
    lv_obj_set_height(ui_Image_Particle2, 240);
    lv_obj_set_width(ui_Image_Particle2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_Image_Particle2, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image_Particle2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image_Particle2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_blend_mode(ui_Image_Particle2, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image_Particle3 = lv_img_create(ui_Particle_Group);
    lv_img_set_src(ui_Image_Particle3, &ui_img_particle_2_png);
    lv_obj_set_height(ui_Image_Particle3, 240);
    lv_obj_set_width(ui_Image_Particle3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_Image_Particle3, 3);
    lv_obj_set_y(ui_Image_Particle3, 0);
    lv_obj_set_align(ui_Image_Particle3, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image_Particle3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image_Particle3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_blend_mode(ui_Image_Particle3, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Wave_Group = lv_obj_create(ui_Group_Battery_Indicator);
    lv_obj_set_width(ui_Wave_Group, 50);
    lv_obj_set_height(ui_Wave_Group, 120);
    lv_obj_set_align(ui_Wave_Group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Wave_Group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Wave_Group, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Wave_Group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Wave_Group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Wave_Group, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Wave1 = lv_img_create(ui_Wave_Group);
    lv_img_set_src(ui_Wave1, &ui_img_water_2_png);
    lv_obj_set_width(ui_Wave1, 206);
    lv_obj_set_height(ui_Wave1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Wave1, 0);
    lv_obj_set_y(ui_Wave1, 66);
    lv_obj_set_align(ui_Wave1, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_Wave1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Wave1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Wave2 = lv_img_create(ui_Wave_Group);
    lv_img_set_src(ui_Wave2, &ui_img_water_1_png);
    lv_obj_set_width(ui_Wave2, 206);
    lv_obj_set_height(ui_Wave2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Wave2, 0);
    lv_obj_set_y(ui_Wave2, 70);
    lv_obj_add_flag(ui_Wave2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Wave2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image_Battery_BG = lv_img_create(ui_Group_Battery_Indicator);
    lv_img_set_src(ui_Image_Battery_BG, &ui_img_battery_bg_png);
    lv_obj_set_width(ui_Image_Battery_BG, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image_Battery_BG, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image_Battery_BG, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image_Battery_BG, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image_Battery_BG, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Image_Battery_BG, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Image_Battery_BG, lv_color_hex(0x438DB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Image_Battery_BG, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Image_Battery_BG, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Image_Battery_BG, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image_Flash = lv_img_create(ui_Group_Battery_Indicator);
    lv_img_set_src(ui_Image_Flash, &ui_img_icn_charge_png);
    lv_obj_set_width(ui_Image_Flash, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image_Flash, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image_Flash, -13);
    lv_obj_set_y(ui_Image_Flash, 0);
    lv_obj_set_align(ui_Image_Flash, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Image_Flash, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image_Flash, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
}

void ui_init(lv_obj_t * ui_Driving)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_Driving_screen_init(ui_Driving);
    // ui____initial_actions0 = lv_obj_create(NULL);
    // lv_disp_load_scr(ui_Driving);
}
