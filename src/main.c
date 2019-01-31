#include "include/ds3231.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "inc/hw_i2c.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

void uartConfigure(uint32_t baudRate) {
  // Enable the GPIO Peripheral used by the UART.
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {
  }

  // Enable UART0
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)) {
  }

  // Configure GPIO Pins for UART mode.
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  // Use the internal 16MHz oscillator as the UART clock source.
  UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

  // Initialize the UART for console I/O.
  UARTStdioConfig(0, baudRate, 16000000);
}

#define UART_BAUD 115200

int main(void) {
  ROM_FPULazyStackingEnable();

  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                 SYSCTL_OSC_MAIN);

  uartConfigure(UART_BAUD);
  UARTprintf("Starting\n");

  Ds3231_time newTime = {
      .is_12_form = false,
      .second = 40,
      .minute = 39,
      .hour = 12,

      .weekDay = 4,
      .day = 31,
      .month = 1,
      .year = 2019,
  };

  ds3231_init();
  ds3231_set_time(&newTime, true);

  for (;;) {
    Ds3231_time currTime;
    ds3231_get_time(&currTime);
    UARTprintf("time: %d:%d:%d, date: %d/%d/%d\n", currTime.hour,
               currTime.minute, currTime.second, currTime.month, currTime.day,
               currTime.year);

    for (uint32_t i = 0; i < 700000; ++i) {
      // delay
    }
  }

  return 0;
}
