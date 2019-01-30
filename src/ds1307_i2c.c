#include "ds1307_i2c.h"
#include "ds1307_hw.h"
#include "include/ds1307.h"

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

static void ds1307_i2c_master_send(const Ds1307 *ds, const uint8_t data,
                                   const uint32_t mode) {
  I2CMasterSlaveAddrSet(ds->i2c_base, DS1307_ADDR, false);
  I2CMasterDataPut(ds->i2c_base, data);
  I2CMasterControl(ds->i2c_base, mode);
  ds1307_i2c_wait_master(ds);
}

void ds1307_i2c_read_regs(const Ds1307 *ds, const uint8_t startAddr,
                          uint8_t *recvData, const uint8_t count) {
  ds1307_i2c_wait_bus(ds);
  ds1307_i2c_master_send(ds, startAddr, I2C_MASTER_CMD_BURST_SEND_START);

  I2CMasterSlaveAddrSet(ds->i2c_base, DS1307_ADDR, true);
  I2CMasterControl(ds->i2c_base, I2C_MASTER_CMD_BURST_RECEIVE_START);
  ds1307_i2c_wait_master(ds);
  recvData[0] = I2CMasterDataGet(ds->i2c_base);

  uint8_t index = 1;
  for (index = 1; index < count - 1; ++index) {
    I2CMasterSlaveAddrSet(ds->i2c_base, DS1307_ADDR, true);
    I2CMasterControl(ds->i2c_base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
    ds1307_i2c_wait_master(ds);
    recvData[index] = I2CMasterDataGet(ds->i2c_base);
  }

  I2CMasterSlaveAddrSet(ds->i2c_base, DS1307_ADDR, true);
  I2CMasterControl(ds->i2c_base, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
  ds1307_i2c_wait_master(ds);
  ds1307_i2c_wait_bus(ds);
  recvData[index] = I2CMasterDataGet(ds->i2c_base);
}

void ds1307_i2c_write_regs(const Ds1307 *ds, const uint8_t startAddr,
                           uint8_t *data, const uint32_t count) {
  ds1307_i2c_wait_bus(ds);
  ds1307_i2c_master_send(ds, startAddr, I2C_MASTER_CMD_BURST_SEND_START);

  uint32_t index;
  for (index = 0; index < count - 1; ++index) {
    ds1307_i2c_master_send(ds, data[index], I2C_MASTER_CMD_BURST_SEND_CONT);
  }

  ds1307_i2c_master_send(ds, data[index], I2C_MASTER_CMD_BURST_SEND_FINISH);
  ds1307_i2c_wait_bus(ds);
  recvData[index] = I2CMasterDataGet(ds->i2c_base);
}

void ds1307_i2c_write_reg(const Ds1307 *ds, const uint8_t addr,
                          const uint8_t data) {
  ds1307_i2c_wait_bus(ds);

  ds1307_i2c_master_send(ds, addr, I2C_MASTER_CMD_BURST_SEND_START);
  ds1307_i2c_master_send(ds, data, I2C_MASTER_CMD_BURST_SEND_FINISH);

  ds1307_i2c_wait_bus(ds);
}

void ds1307_i2c_wait_master(const Ds1307 *ds) {
  while (I2CMasterBusy(ds->i2c_base)) {
    // wait until the master is not busy
  }
}

void ds1307_i2c_wait_bus(const Ds1307 *ds) {
  while (I2CMasterBusBusy(ds->i2c_base)) {
    // wait until the bus is not busy
  }
}
