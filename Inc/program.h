#pragma once

#include "stm32f4xx_hal.h"

// Waveshare setups
#define PI 3.14159265358979323846
#define WIDTH EPD_4IN2_V2_WIDTH
#define HEIGHT EPD_4IN2_V2_HEIGHT

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
void heartbeat();