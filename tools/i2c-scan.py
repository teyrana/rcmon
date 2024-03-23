# SPDX-FileCopyrightText: 2017 Limor Fried for Adafruit Industries
#
# SPDX-License-Identifier: MIT

# pylint: disable=broad-except, eval-used, unused-import

"""CircuitPython I2C Device Address Scan"""
import time
import board
# import busio


i2c = board.I2C()

while not i2c.try_lock():
    pass


try:
    while True:

        print("-" * 40)
        print("I2C SCAN")
        print("-" * 40)
        while True:
            # for addr in range(0.256):
            for addr in i2c.scan():
                print("    - found: ", hex(addr))

            time.sleep(6)


finally:  # unlock the i2c bus when ctrl-c'ing out of the loop
    i2c.unlock()

