#ifndef PROGRAM_H
#define PROGRAM_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "GUI_Paint.h"
#include "EPD_4in2_V2.h"
#include "fonts.h"
#include "debug.h"
#include "lvgl.h"

#define PI 3.14159265358979323846
#define WIDTH EPD_4IN2_V2_WIDTH
#define HEIGHT EPD_4IN2_V2_HEIGHT

#define TFT_HOR_RES EPD_4IN2_V2_WIDTH
#define TFT_VER_RES EPD_4IN2_V2_HEIGHT

static uint32_t my_tick_cb(void)
{
    return HAL_GetTick();
}

static void my_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    /*Write px_map to the area->x1, area->x2, area->y1, area->y2 area of the
     *frame buffer or external display controller. */
}

typedef struct
{
    float x, y, z;
} Point3D;

typedef struct
{
    Point3D points[8];
} Cube;

void setup();
void loop();
void updateBusyLED();
void displayNumber(int);
void displayTick();

#endif // PROGRAM_H