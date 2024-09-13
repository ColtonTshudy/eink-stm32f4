#include "program.h"

// TODO add framerate counter to loop()

uint8_t *imageBuffer;

extern TIM_HandleTypeDef htim2;

void setup()
{
    if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
    {
        Error_Handler();
    }

    EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    DEV_Delay_ms(500);

    // create image buffer
    UWORD imageSize = ((EPD_4IN2_V2_WIDTH % 8 == 0) ? (EPD_4IN2_V2_WIDTH / 8) : (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;
    imageBuffer = (UBYTE *)malloc(imageSize);
    Debug("Image buffer: %u bytes", imageSize);

    // clear the image buffer
    Paint_SelectImage(imageBuffer);
    Paint_NewImage(imageBuffer, 200, 50, 0, WHITE);
}

void loop()
{
    displayTick();
    // static uint32_t lastTime = 0;

    // if (lastTime - HAL_GetTick() > 5000)
    // {
    //     fastUpdateTest();
    //     lastTime = HAL_GetTick();
    // }
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

void displayTick()
{
    static sFONT *Font = &Font20;
    static uint16_t Color_Foreground = BLACK;
    static uint16_t Color_Background = WHITE;
    uint16_t x = Paint.Width - Font->Width;
    uint16_t y = 0;
    static uint8_t value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    uint16_t dx = Font->Width;

    uint32_t tick = HAL_GetTick();

    Paint_Clear(WHITE);

    Debug("On tick %lu", tick);

    while (tick > 0)
    {
        uint8_t curTickDigit = tick % 10;
        Paint_DrawChar(x, y, value[curTickDigit], Font, Color_Foreground, Color_Background);
        Debug("  tick: %lu,\t curtick: %u,\t coordinate: [%u, %u]", tick, curTickDigit, x, y);

        tick /= 10;
        x -= dx;
    }

    EPD_4IN2_V2_PartialDisplay(imageBuffer, 80, 200, 280, 250);

    HAL_Delay(1);
}

void fastUpdateTest()
{
    printf("Partial refresh\r\n");
    Paint_NewImage(imageBuffer, 200, 50, 0, WHITE);
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 10;
    for (;;)
    {
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60)
        {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60)
            {
                sPaint_time.Hour = sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24)
                {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        Paint_Clear(WHITE);
        Paint_DrawTime(20, 10, &sPaint_time, &Font20, WHITE, BLACK);
        EPD_4IN2_V2_PartialDisplay(imageBuffer, 80, 200, 280, 250);
        DEV_Delay_ms(500); // Analog clock 1s
        num = num - 1;
        if (num == 0)
        {
            break;
        }
    }
}