# ds3231_tivaC

ds3231 RTC port for the tivaC. Customized for personal use so read the code carefully before using

## Credits

I took the register definition from Google Android source code at [here](1).

## Features

- Reset and read data-time in 12 and 24 hour format
- 4 clock frequency derived from the onboard crystal
- Turn on/off the oscillator
- 2 sets of alarm with interrupt

[1]: https://android.googlesource.com/device/ti/bootloader/uboot/+/master/drivers/rtc/ds3231.c