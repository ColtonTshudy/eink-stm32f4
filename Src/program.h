#ifndef PROGRAM_H
#define PROGRAM_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "GUI_Paint.h"
#include "EPD_4in2_V2.h"
#include "fonts.h"

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

void setup(void);
void loop(void);
void updateBusyLED();
void displayNumber(int);

#endif // PROGRAM_H