#!/usr/bin/python
import smbus

bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

DEVICE_ADDRESS = 0x04      #7 bit address (will be left shifted to add the read write bit)
MESSAGE_BEGIN = 0x16
MESSAGE_END = 0x06

#Write an array of registers
request_values = [0x53, MESSAGE_END]
bus.write_i2c_block_data(DEVICE_ADDRESS, MESSAGE_BEGIN, request_values)


#Read an array of registers
return_data = bus.read_i2c_block_data(DEVICE_ADDRESS, 3)

import urllib

req = "http://localhost:8083/fhem?cmd=setreading%20Sensor_Arduino_TMP_1%20state%20"

req += str(data[1])

urllib.urlopen(req)