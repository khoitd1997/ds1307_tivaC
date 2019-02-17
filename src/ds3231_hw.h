#ifndef _ds3231_HW_H
#define _ds3231_HW_H
#ifdef __cplusplus
extern "C" {
#endif

#include "inc/hw_memmap.h"

// source:
// https://android.googlesource.com/device/ti/bootloader/uboot/+/master/drivers/rtc/ds3231.c

/*
 * RTC register addresses
 */
#define DS3231_SEC_REG_ADDR 0x0
#define DS3231_MIN_REG_ADDR 0x1
#define DS3231_HR_REG_ADDR 0x2
#define DS3231_DAY_REG_ADDR 0x3
#define DS3231_DATE_REG_ADDR 0x4
#define DS3231_MON_REG_ADDR 0x5
#define DS3231_YR_REG_ADDR 0x6

#define DS3231_CTL_REG_ADDR 0x0e
#define DS3231_STAT_REG_ADDR 0x0f
/*
 * RTC control register bits
 */
#define DS3231_CTL_BIT_A1IE 0x1  /* Alarm 1 interrupt enable     */
#define DS3231_CTL_BIT_A2IE 0x2  /* Alarm 2 interrupt enable     */
#define DS3231_CTL_BIT_INTCN 0x4 /* Interrupt control            */
#define DS3231_CTL_BIT_RS1 0x8   /* Rate select 1                */
#define DS3231_CTL_BIT_RS2 0x10  /* Rate select 2                */
#define DS3231_CTL_BIT_DOSC 0x80 /* Disable Oscillator           */
/*
 * RTC status register bits
 */
#define DS3231_STAT_BIT_A1F 0x1  /* Alarm 1 flag                 */
#define DS3231_STAT_BIT_A2F 0x2  /* Alarm 2 flag                 */
#define DS3231_STAT_BIT_OSF 0x80 /* Oscillator stop flag         */

#define DS3231_ADDR 0x68

// TivaC specific stuffs
#define DS3231_I2C_BASE I2C1_BASE

#define TOTAL_TIME_REGISTER 7

#ifdef __cplusplus
}
#endif
#endif