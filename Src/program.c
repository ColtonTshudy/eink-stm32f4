#include "program.h"
#include "debugger.h"
#include "display_epaper_42.h"
// #include "lvgl.h"

void setup()
{
    printf("Hello, world!");
    rtt_init();
}

void loop()
{
}

void updateBusyLED()
{
    if (HAL_GPIO_ReadPin(BUSY_GPIO_Port, BUSY_Pin))
    {
        // display is busy
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
    }
    else
    {
        // display is not busy
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
    }
}