#include "include/ds3231.h"

#include "ds3231_hw.h"
#include "ds3231_i2c.h"

#include "tiva_utils/bit_manipulation.h"

#define CURRENT_CENTURY 2000

static uint8_t int_to_bcd(const uint8_t num) {
  return (((num / 10) << 4) | (num % 10));
}

static uint8_t bcd_to_int(const uint8_t num) {
  return (((num >> 4) * 10) + bit_get((num), 0xf));
}

// also turn on the clock
void ds3231_set_time(const ds3231 *ds, const ds3231_time *time) {
  uint8_t time_regs[TOTAL_TIME_REGISTER] = {0};
  bit_set(time_regs[0], BIT(7) | int_to_bcd(time->second));
  bit_set(time_regs[1], int_to_bcd(time->minute));

  uint8_t hourMode = 0;
  if (time->is_12_form) {
    hourMode = BIT(6) | ((time->is_pm) ? BIT(5) : 0);
  }
  bit_set(time_regs[2], int_to_bcd(time->hour) | hourMode);

  bit_set(time_regs[3], int_to_bcd(time->weekDay));
  bit_set(time_regs[4], int_to_bcd(time->day));
  bit_set(time_regs[5], int_to_bcd(time->month));
  bit_set(time_regs[6], int_to_bcd(time->year - CURRENT_CENTURY));

  ds3231_i2c_write_regs(ds, DS3231_SEC_REG_ADDR, time_regs,
                        TOTAL_TIME_REGISTER);
}

void ds3231_get_time(const ds3231 *ds, ds3231_time *time) {
  uint8_t time_regs[TOTAL_TIME_REGISTER] = {0};
  ds3231_i2c_read_regs(ds, DS3231_SEC_REG_ADDR, time_regs, TOTAL_TIME_REGISTER);
  time->second = bcd_to_int(time_regs[0]);
  time->minute = bcd_to_int(time_regs[1]);

  uint8_t rawHour = time_regs[2];
  if (bit_get(rawHour, BIT(6))) {
    time->is_12_form = true;
    time->hour = bcd_to_int(rawHour);
    time->is_pm = bit_get(rawHour, BIT(5));
  } else {
    time->is_12_form = false;
    time->hour = bcd_to_int(rawHour);
  }

  time->weekDay = bcd_to_int(time_regs[3]);
  time->day = bcd_to_int(time_regs[4]);
  time->month = bcd_to_int(time_regs[5]);
  time->year = bcd_to_int(time_regs[6]) + CURRENT_CENTURY;
}

void ds3231_off(const ds3231 *ds) {
  ds3231_i2c_write_reg(ds, DS3231_SEC_REG_ADDR, 0);
}