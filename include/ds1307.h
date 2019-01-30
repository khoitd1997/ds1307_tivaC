#ifndef _DS1307_H
#define _DS1307_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Used for reseting ds1307 time
 *
 */
typedef struct {
  bool is_24_form;
  uint8_t second;
  uint8_t minute;
  uint8_t hour;

  uint8_t weekDay; ///< 1-7 for Monday-Sunday
  uint8_t day;     ///< 1-31 for each day of month
  uint8_t month;
  uint32_t year;

} Ds1307_time;

typedef struct {
  bool is_24_form;
  uint32_t i2c_base;
} Ds1307;

#ifdef __cplusplus
}
#endif
#endif