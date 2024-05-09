SET(SOURCES screens/ui_StartPage.c
    screens/ui_HomePage.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_logo1_png.c
    images/ui_img_99_png.c
    fonts/ui_font_DigitalFont22b1.c
    fonts/ui_font_DigitalFont30b1.c)

add_library(ui ${SOURCES})
