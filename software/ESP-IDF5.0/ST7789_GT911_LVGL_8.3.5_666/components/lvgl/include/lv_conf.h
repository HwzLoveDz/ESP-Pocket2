/**
 * @file lv_conf.h
 * Configuration file for v8.3.4
 *
 */
/*
 * COPY THIS FILE AS lv_conf.h
 */

/*
 * 如果你需要更改LVGL设置，
 * 我推荐你修改“components/lvgl/Kconfig.projbuild”，参考“components/lvgl/lvgl/Kconfig”，
 * 之后在 sdkconfig 中修改对应位置，再进行重新编译，因为这一部分一般并不需要经常修改，所以不建议在此处修改。
 ^ 该文件被 lvgl.h 引用。
 ! 实际只有 Kconfig.projbuild 生效，更改 Kconfig 不会有任何效果。
 */

/* clang-format off */
#if 0 /*Set it to "1" to enable the content*/

#ifndef LV_CONF_H
#define LV_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 * CUSTOM SETTINGS
 *********************/

#ifdef __cplusplus
}
#endif

#endif /*LV_CONF_H*/

#endif /*End of "Content enable"*/
