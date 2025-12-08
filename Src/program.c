#include "program.h"
#include "debugger.h"
#include <stdio.h>
#include "lvgl.h"
#include "EPD_4in2_V2.h"

#define EPD_WIDTH 400
#define EPD_HEIGHT 300
#define BUF_SIZE (EPD_WIDTH / 8 * EPD_HEIGHT) + 8

// LVGL render buffers
static uint8_t buf[BUF_SIZE];
static lv_display_t *display;

// E-paper API frame buffer
// static uint8_t epaper_fb[EPD_WIDTH * EPD_HEIGHT / 8];

/**
 * Flush callback - converts LVGL framebuffer to e-paper format and displays it
 * Supports both full and partial refresh modes
 */
void epd_flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    px_map += 8;
    LV_LOG_USER("Drawing area from x: %lu to %lu, y: %lu to %lu", area->x1, area->x2, area->y1, area->y2);

    EPD_4IN2_V2_PartialDisplay(px_map,
                               area->x1, area->y1,
                               area->x2, area->y2);

    // For full screen refresh
    // if (area->x1 == 0 && area->y1 == 0 &&
    //     area->x2 == EPD_WIDTH - 1 &&
    //     area->y2 == EPD_HEIGHT - 1)
    // {
    //     EPD_4IN2_V2_Display_Fast(px_map);
    // }
    // else
    // {
    //     // For partial updates
    //     EPD_4IN2_V2_PartialDisplay(px_map,
    //                                area->x1, area->y1,
    //                                area->x2, area->y2);
    // }

    lv_display_flush_ready(display);
}

void setup()
{
    rtt_init();
    printf("Hello, world!\r\n");

    printf("1\r\n");
    EPD_4IN2_V2_Init_Fast(Seconds_1S);
    EPD_4IN2_V2_Clear();

    printf("1.5\r\n");
    lv_init();
    printf("2\r\n");
    lv_tick_set_cb(HAL_GetTick);
    printf("3\r\n");
    display = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    lv_display_set_color_format(display, LV_COLOR_FORMAT_I1);

    printf("4\r\n");
    lv_display_set_buffers(display, buf, NULL, BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, epd_flush_cb);
    printf("5\r\n");

    // lv_theme_mono_init(display, true, &lv_font_montserrat_14);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_white(), 0);
    lv_label_set_text(label, "Hello world");
    lv_obj_center(label);
}

void loop()
{
    lv_timer_handler();
    heartbeat();
    HAL_Delay(100);
}

void heartbeat()
{
    uint16_t blink_duration = 500;
    static uint32_t last_time = 0;
    uint32_t this_time = HAL_GetTick();
    if (this_time - last_time > blink_duration)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        last_time = this_time;
        printf("Heartbeat\r\n");
    }
}
