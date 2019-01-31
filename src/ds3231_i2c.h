#ifndef _ds3231_I2C_H
#define _ds3231_I2C_H
#ifdef __cplusplus
extern "C" {
#endif

#include "include/ds3231.h"
#include <stdint.h>

void ds3231_i2c_write_regs(const ds3231 *ds, const uint8_t startAddr,
                           uint8_t *data, const uint32_t count);
void ds3231_i2c_write_reg(const ds3231 *ds, const uint8_t addr,
                          const uint8_t data);
void ds3231_i2c_read_regs(const ds3231 *ds, const uint8_t startAddr,
                          uint8_t *recvData, const uint8_t count);

void ds3231_i2c_wait_master(const ds3231 *ds);
void ds3231_i2c_wait_bus(const ds3231 *ds);

#ifdef __cplusplus
}
#endif
#endif