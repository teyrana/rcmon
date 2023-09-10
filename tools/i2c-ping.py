# SPDX-FileCopyrightText: 2022 Kattni Rembor for Adafruit Industries
# SPDX-License-Identifier: MIT

"""CircuitPython I2C Device Address Scan For Feather/rp2040"""

import time
import board

i2c = board.I2C()

while not i2c.try_lock():
    pass



try:
    while True:
        addr = 0x48

        # Create library object on our I2C port
        a2d = adafruit_tsl2591.TSL2591(i2c)

        # Use the object to print the sensor readings
        while True:
            print("Lux:", tsl2591.lux)
            time.sleep(0.5)
            
        print(f"I2C ping: @ 0x{addr:02X}: NYI")

        time.sleep(6)

finally:  # unlock the i2c bus when ctrl-c'ing out of the loop
    i2c.unlock()

