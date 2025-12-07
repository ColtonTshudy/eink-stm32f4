#include "program.h"
#include "debugger.h"
#include "display_epaper_42.h"
#include <stdio.h>
// #include "lvgl.h"

void setup()
{
    rtt_init();
    printf("Hello, world!");
}

void loop()
{
    heartbeat();
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
    }
}
