#!/usr/bin/python

import smbus

bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

DEVICE_ADDRESS = 0x04      #7 bit address (will be left shifted to add the read write bit)
MESSAGE_BEGIN = 0x16
MESSAGE_END = 0x06

input_var = 1

if input_var == 0:

        relaystatus = 0x00

if input_var == 1:

        relaystatus = 0x01

#Write an array of registers
ledout_values = [0x52, 0x24, relaystatus, MESSAGE_END]
bus.write_i2c_block_data(DEVICE_ADDRESS, MESSAGE_BEGIN, ledout_values)
