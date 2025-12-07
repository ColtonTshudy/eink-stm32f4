/*****************************************************************************
 * LVGL Initialization for Waveshare 4.2" E-Paper Display V2
 * Display: 400x300 Black & White
 * Features: Full and partial refresh support
 *****************************************************************************/

#ifndef LVGL_EPAPER_INIT_H
#define LVGL_EPAPER_INIT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Initialize the e-paper display and LVGL
 * @param enable_partial_refresh:
 *   true  = Fast mode with partial updates (faster, may have ghosting)
 *   false = Standard mode with full refresh only (slower, no ghosting)
 * Call this once at startup
 */
void lvgl_epaper_init(bool enable_partial_refresh);

/**
 * Enable or disable partial refresh at runtime
 * @param enable: true to enable partial updates, false for full refresh only
 */
void lvgl_epaper_set_partial_mode(bool enable);

/**
 * Force a full screen refresh (useful to clear ghosting after many partial updates)
 */
void lvgl_epaper_full_refresh(void);

/**
 * Get refresh statistics
 * @param full_count: Pointer to store full refresh count (can be NULL)
 * @param partial_count: Pointer to store partial refresh count (can be NULL)
 */
void lvgl_epaper_get_stats(uint32_t *full_count, uint32_t *partial_count);

/**
 * Put display to sleep mode
 * Call this to save power when done
 */
void lvgl_epaper_sleep(void);

#endif // LVGL_EPAPER_INIT_H