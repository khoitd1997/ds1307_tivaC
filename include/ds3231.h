#ifndef _ds3231_H
#define _ds3231_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

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
 * @brief Used for reseting ds3231 time
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

typedef struct {
  uint32_t i2c_base;
} Ds3231;

void ds3231_init();
void ds3231_set_time(const Ds3231_time *time, const bool turn_clock_on);
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