
""" MicroPython I2C Device Address Scan"""

import time

from machine import Pin, I2C 

# Pinout for RPI-Pico (vanilla)
# i2c0 = I2C(0, scl=Pin(1), sda=Pin(0), freq=100000) 
i2c0 = I2C(0)

#i2c1 = I2C(1, scl=Pin(7), sda=Pin(6), freq=100000)

i2c.scan()
