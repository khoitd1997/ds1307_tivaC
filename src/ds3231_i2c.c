#include "ds3231_i2c.h"
#include "ds3231.h"
#include "ds3231_hw.h"

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

static void ds3231_i2c_master_send(const uint8_t data, const uint32_t mode) {
  I2CMasterSlaveAddrSet(DS3231_I2C_BASE, DS3231_ADDR, false);
  I2CMasterDataPut(DS3231_I2C_BASE, data);
  I2CMasterControl(DS3231_I2C_BASE, mode);
  ds3231_i2c_wait_master();
}

void ds3231_i2c_read_regs(const uint8_t startAddr, uint8_t *recvData, const uint8_t count) {
  ds3231_i2c_wait_bus();
  ds3231_i2c_master_send(startAddr, I2C_MASTER_CMD_BURST_SEND_START);

  I2CMasterSlaveAddrSet(DS3231_I2C_BASE, DS3231_ADDR, true);
  I2CMasterControl(DS3231_I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
  ds3231_i2c_wait_master();
  recvData[0] = I2CMasterDataGet(DS3231_I2C_BASE);

  uint8_t index = 1;
  for (index = 1; index < count - 1; ++index) {
    I2CMasterSlaveAddrSet(DS3231_I2C_BASE, DS3231_ADDR, true);
    I2CMasterControl(DS3231_I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
    ds3231_i2c_wait_master();
    recvData[index] = I2CMasterDataGet(DS3231_I2C_BASE);
  }

  I2CMasterSlaveAddrSet(DS3231_I2C_BASE, DS3231_ADDR, true);
  I2CMasterControl(DS3231_I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
  ds3231_i2c_wait_master();
  ds3231_i2c_wait_bus();
  recvData[index] = I2CMasterDataGet(DS3231_I2C_BASE);
}

void ds3231_i2c_read_reg(const uint8_t addr, uint8_t *out) {
  ds3231_i2c_wait_bus();
  ds3231_i2c_master_send(addr, I2C_MASTER_CMD_BURST_SEND_START);

  I2CMasterSlaveAddrSet(DS3231_I2C_BASE, DS3231_ADDR, true);
  I2CMasterControl(DS3231_I2C_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
  ds3231_i2c_wait_master();
  *out = I2CMasterDataGet(DS3231_I2C_BASE);
}

void ds3231_i2c_write_regs(const uint8_t startAddr, uint8_t *data, const uint32_t count) {
  ds3231_i2c_wait_bus();
  ds3231_i2c_master_send(startAddr, I2C_MASTER_CMD_BURST_SEND_START);

  uint32_t index;
  for (index = 0; index < count - 1; ++index) {
    ds3231_i2c_master_send(data[index], I2C_MASTER_CMD_BURST_SEND_CONT);
  }

  ds3231_i2c_master_send(data[index], I2C_MASTER_CMD_BURST_SEND_FINISH);
  ds3231_i2c_wait_bus();
  data[index] = I2CMasterDataGet(DS3231_I2C_BASE);
}

void ds3231_i2c_write_reg(const uint8_t addr, const uint8_t data) {
  ds3231_i2c_wait_bus();

  ds3231_i2c_master_send(addr, I2C_MASTER_CMD_BURST_SEND_START);
  ds3231_i2c_master_send(data, I2C_MASTER_CMD_BURST_SEND_FINISH);

  ds3231_i2c_wait_bus();
}

void ds3231_i2c_wait_master() {
  while (I2CMasterBusy(DS3231_I2C_BASE)) {
    // wait until the master is not busy
  }
}

void ds3231_i2c_wait_bus() {
  while (I2CMasterBusBusy(DS3231_I2C_BASE)) {
    // wait until the bus is not busy
  }
}
