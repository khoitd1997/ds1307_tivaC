#ifndef _ds3231_I2C_H
#define _ds3231_I2C_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ds3231.h"

void ds3231_i2c_write_regs(const uint8_t startAddr, uint8_t *data, const uint32_t count);
void ds3231_i2c_write_reg(const uint8_t addr, const uint8_t data);
void ds3231_i2c_read_regs(const uint8_t startAddr, uint8_t *recvData, const uint8_t count);
void ds3231_i2c_read_reg(const uint8_t addr, uint8_t *out);

void ds3231_i2c_wait_master();
void ds3231_i2c_wait_bus();

#ifdef __cplusplus
}
#endif
#endif