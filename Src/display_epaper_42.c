/*****************************************************************************
 * LVGL Initialization for Waveshare 4.2" E-Paper Display V2
 * Display: 400x300 Black & White
 * LVGL Version: v9.x
 * Features: Full refresh and partial refresh support
 *****************************************************************************/

#include "lvgl.h"
#include "EPD_4in2_V2.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Display dimensions
#define EPD_WIDTH 400
#define EPD_HEIGHT 300

// LVGL display buffer (1/10th of screen for memory efficiency)
#define BUFFER_SIZE (EPD_WIDTH * EPD_HEIGHT / 20)

// Partial refresh configuration
#define PARTIAL_REFRESH_ENABLED 1  // Set to 0 to disable partial updates
#define FULL_REFRESH_THRESHOLD 0.8 // If area > 80% of screen, do full refresh

// Static buffers
static lv_color_t buf1[BUFFER_SIZE];
static lv_display_t *disp;

// E-paper framebuffer (1 bit per pixel = 400*300/8 bytes)
static UBYTE epaper_fb[EPD_WIDTH * EPD_HEIGHT / 8];

// Refresh mode tracking
static bool use_partial_refresh = true;
static uint32_t full_refresh_counter = 0;
static uint32_t partial_refresh_counter = 0;

/**
 * Flush callback - converts LVGL framebuffer to e-paper format and displays it
 * Supports both full and partial refresh modes
 */
static void epaper_flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    int32_t x, y;
    lv_color_t *color_p = (lv_color_t *)px_map;

    // Convert LVGL color format to 1-bit monochrome
    for (y = area->y1; y <= area->y2; y++)
    {
        for (x = area->x1; x <= area->x2; x++)
        {
            // Calculate byte and bit position in framebuffer
            uint32_t byte_index = (y * EPD_WIDTH + x) / 8;
            uint8_t bit_index = x % 8;

            // Get pixel brightness (convert to monochrome)
            lv_color_t color = *color_p;
            uint8_t brightness = lv_color_brightness(color);

            // Threshold: >128 = white (0), <=128 = black (1)
            if (brightness > 128)
            {
                epaper_fb[byte_index] &= ~(0x80 >> bit_index); // White
            }
            else
            {
                epaper_fb[byte_index] |= (0x80 >> bit_index); // Black
            }

            color_p++;
        }
    }

    // Determine if we should do full or partial refresh
    bool is_full_screen = (area->x1 == 0 && area->y1 == 0 &&
                           area->x2 == EPD_WIDTH - 1 && area->y2 == EPD_HEIGHT - 1);

    uint32_t area_pixels = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1);
    uint32_t total_pixels = EPD_WIDTH * EPD_HEIGHT;
    float area_ratio = (float)area_pixels / total_pixels;

#if PARTIAL_REFRESH_ENABLED
    if (use_partial_refresh && !is_full_screen && area_ratio < FULL_REFRESH_THRESHOLD)
    {
        // Use partial refresh for small areas
        EPD_4IN2_V2_PartialDisplay(epaper_fb, area->x1, area->y1, area->x2, area->y2);
        partial_refresh_counter++;
    }
    else
    {
        // Use full refresh for large areas or when forced
        EPD_4IN2_V2_Display(epaper_fb);
        full_refresh_counter++;
    }
#else
    // Always use full refresh if partial is disabled
    EPD_4IN2_V2_Display(epaper_fb);
    full_refresh_counter++;
#endif

    // Inform LVGL that flushing is done
    lv_display_flush_ready(display);
}

/**
 * Initialize the e-paper display and LVGL
 * mode: true = use partial refresh (fast), false = full refresh only (no ghosting)
 */
void lvgl_epaper_init(bool enable_partial_refresh)
{
    // Initialize LVGL
    lv_init();

    // Initialize e-paper display hardware
    if (enable_partial_refresh)
    {
        // Fast mode for partial updates
        EPD_4IN2_V2_Init_Fast(Seconds_1S);
        use_partial_refresh = true;
    }
    else
    {
        // Standard mode for full refresh only
        EPD_4IN2_V2_Init();
        use_partial_refresh = false;
    }

    EPD_4IN2_V2_Clear();

    // Clear framebuffer (all white)
    memset(epaper_fb, 0x00, sizeof(epaper_fb));

    // Reset counters
    full_refresh_counter = 0;
    partial_refresh_counter = 0;

    // Create display with simplified v9 API
    disp = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    lv_display_set_flush_cb(disp, epaper_flush_cb);
    lv_display_set_buffers(disp, buf1, NULL, BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);
}

/**
 * Enable or disable partial refresh at runtime
 */
void lvgl_epaper_set_partial_mode(bool enable)
{
    use_partial_refresh = enable;
}

/**
 * Force a full refresh (clears ghosting)
 */
void lvgl_epaper_full_refresh(void)
{
    EPD_4IN2_V2_Display(epaper_fb);
    full_refresh_counter++;
}

/**
 * Get refresh statistics
 */
void lvgl_epaper_get_stats(uint32_t *full_count, uint32_t *partial_count)
{
    if (full_count)
        *full_count = full_refresh_counter;
    if (partial_count)
        *partial_count = partial_refresh_counter;
}

/**
 * Put display to sleep (call when done)
 */
void lvgl_epaper_sleep(void)
{
    EPD_4IN2_V2_Sleep();
}