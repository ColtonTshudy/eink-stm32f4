#include "program.h"

void setup()
{
    EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    DEV_Delay_ms(500);
}

void loop()
{
    static uint32_t lastTime = 0;

    if (lastTime - HAL_GetTick() > 5000)
    {
        displayNumber(HAL_GetTick());
        lastTime = HAL_GetTick();
    }

    updateBusyLED();
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

void displayNumber(int number)
{
    UBYTE *BlackImage;
    UWORD Imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0) ? (EPD_4IN2_V2_WIDTH / 8) : (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;

    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\n");
        return;
    }

    Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    char str[3];
    sprintf(str, "%d", number);

    // Calculate position to center the text
    int stringWidth = strlen(str) * Font24.Width;
    int x = (EPD_4IN2_V2_WIDTH - stringWidth) / 2;
    int y = (EPD_4IN2_V2_HEIGHT - Font24.Height) / 2;

    Paint_DrawString_EN(x, y, str, &Font24, WHITE, BLACK);

    EPD_4IN2_V2_Display_Fast(BlackImage);

    free(BlackImage);
}