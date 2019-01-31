# ds3231_tivaC

ds3231 RTC port for the tivaC. Customized for personal use so read the code carefully before using

## Notes

This code is hardcoded to use i2c0 of the tivaC, to change it you need to change the macro ```DS3231_I2C_BASE``` and either change also the init function or dont't call it and initialize the i2c module on yourself.

## Documentation and Examples

Right now Doxygen style comments are provided in ds3231.h file, I may build the docs and deploy it later

Example of code using the ds3231 is provided in main.c

## Credits

I took the register definition from Google Android source code at [here](1). The logic is just implementation from the datasheet

## Features

- [x] Reset and read data-time in 12 and 24 hour format
- [ ] 4 clock frequency derived from the onboard crystal
- [x] Turn on/off the oscillator
- [ ] 2 sets of alarm with interrupt

[1]: https://android.googlesource.com/device/ti/bootloader/uboot/+/master/drivers/rtc/ds3231.c