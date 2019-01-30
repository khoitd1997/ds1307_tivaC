#ifndef _DS1307_I2C_H
#define _DS1307_I2C_H
#ifdef __cplusplus
extern "C" {
#endif

#include "include/ds1307.h"
#include <stdint.h>

void ds1307_i2c_write_regs(const Ds1307 *ds, const uint8_t startAddr,
                           uint8_t *data, const uint32_t count);
void ds1307_i2c_write_reg(const Ds1307 *ds, const uint8_t addr,
                          const uint8_t data);
void ds1307_i2c_read_regs(const Ds1307 *ds, const uint8_t startAddr,
                          uint8_t *recvData, const uint8_t count);

void ds1307_i2c_wait_master(const Ds1307 *ds);
void ds1307_i2c_wait_bus(const Ds1307 *ds);

#ifdef __cplusplus
}
#endif
#endif