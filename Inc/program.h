#ifndef PROGRAM_H
#define PROGRAM_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "debug.h"
#include "lvgl.h"

// Waveshare setups
#define PI 3.14159265358979323846
#define WIDTH EPD_4IN2_V2_WIDTH
#define HEIGHT EPD_4IN2_V2_HEIGHT

// LVGL setups
#define EPD_WIDTH 400
#define EPD_HEIGHT 300
#define BUFFER_SIZE (EPD_WIDTH * EPD_HEIGHT / 10)

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