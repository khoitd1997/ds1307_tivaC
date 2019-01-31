#include "ds3231_hw.h"
#include "ds3231_i2c.h"
#include "include/ds3231.h"

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_i2c.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

static void ds3231_i2c_master_send(const ds3231 *ds, const uint8_t data,
                                   const uint32_t mode) {
  I2CMasterSlaveAddrSet(ds->i2c_base, DS3231_ADDR, false);
  I2CMasterDataPut(ds->i2c_base, data);
  I2CMasterControl(ds->i2c_base, mode);
  ds3231_i2c_wait_master(ds);
}

void ds3231_i2c_read_regs(const ds3231 *ds, const uint8_t startAddr,
                          uint8_t *recvData, const uint8_t count) {
  ds3231_i2c_wait_bus(ds);
  ds3231_i2c_master_send(ds, startAddr, I2C_MASTER_CMD_BURST_SEND_START);

  I2CMasterSlaveAddrSet(ds->i2c_base, DS3231_ADDR, true);
  I2CMasterControl(ds->i2c_base, I2C_MASTER_CMD_BURST_RECEIVE_START);
  ds3231_i2c_wait_master(ds);
  recvData[0] = I2CMasterDataGet(ds->i2c_base);

  uint8_t index = 1;
  for (index = 1; index < count - 1; ++index) {
    I2CMasterSlaveAddrSet(ds->i2c_base, DS3231_ADDR, true);
    I2CMasterControl(ds->i2c_base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
    ds3231_i2c_wait_master(ds);
    recvData[index] = I2CMasterDataGet(ds->i2c_base);
  }

  I2CMasterSlaveAddrSet(ds->i2c_base, DS3231_ADDR, true);
  I2CMasterControl(ds->i2c_base, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
  ds3231_i2c_wait_master(ds);
  ds3231_i2c_wait_bus(ds);
  recvData[index] = I2CMasterDataGet(ds->i2c_base);
}

void ds3231_i2c_write_regs(const ds3231 *ds, const uint8_t startAddr,
                           uint8_t *data, const uint32_t count) {
  ds3231_i2c_wait_bus(ds);
  ds3231_i2c_master_send(ds, startAddr, I2C_MASTER_CMD_BURST_SEND_START);

  uint32_t index;
  for (index = 0; index < count - 1; ++index) {
    ds3231_i2c_master_send(ds, data[index], I2C_MASTER_CMD_BURST_SEND_CONT);
  }

  ds3231_i2c_master_send(ds, data[index], I2C_MASTER_CMD_BURST_SEND_FINISH);
  ds3231_i2c_wait_bus(ds);
  data[index] = I2CMasterDataGet(ds->i2c_base);
}

void ds3231_i2c_write_reg(const ds3231 *ds, const uint8_t addr,
                          const uint8_t data) {
  ds3231_i2c_wait_bus(ds);

  ds3231_i2c_master_send(ds, addr, I2C_MASTER_CMD_BURST_SEND_START);
  ds3231_i2c_master_send(ds, data, I2C_MASTER_CMD_BURST_SEND_FINISH);

  ds3231_i2c_wait_bus(ds);
}

void ds3231_i2c_wait_master(const ds3231 *ds) {
  while (I2CMasterBusy(ds->i2c_base)) {
    // wait until the master is not busy
  }
}

void ds3231_i2c_wait_bus(const ds3231 *ds) {
  while (I2CMasterBusBusy(ds->i2c_base)) {
    // wait until the bus is not busy
  }
}
