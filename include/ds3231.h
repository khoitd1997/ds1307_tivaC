#ifndef _ds3231_H
#define _ds3231_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Week day and its corresponding number
 *
 */
typedef enum {
  MONDAY = 1,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
} Ds3231_week_day;

/**
 * @brief Used for setting ds3231 time
 *
 */
typedef struct {
  bool is_12_form;
  bool is_pm; // only used for 12-hour format
  uint8_t second;
  uint8_t minute;
  uint8_t hour;

  Ds3231_week_day weekDay; ///< 1-7 for Monday-Sunday
  uint8_t day;             ///< 1-31 for each day of month
  uint8_t month;
  uint32_t year;
} Ds3231_time;

/**
 * @brief Initialize i2c module of tivaC
 *
 */
void ds3231_init();

/**
 * @brief Set the time of the ds3231 according to the struct
 *
 * @param time Time struct for clock new time
 * @param turn_clock_on If true turn on the clock after setting the new time
 */
void ds3231_set_time(const Ds3231_time *time, const bool turn_clock_on);

/**
 * @brief Return current clock time in a time struct
 *
 * @param time The struct to fill the current time in
 */
void ds3231_get_time(Ds3231_time *time);

/**
 * @brief Turn the oscillator off ONLY IF THE RTC IS ON BATTERY, otw do nothing
 *
 */
void ds3231_osc_off();

/**
 * @brief Turn the oscillator on if it's off and on battery
 *
 */
void ds3231_osc_on();

#ifdef __cplusplus
}
#endif
#endif