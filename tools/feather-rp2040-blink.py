# SPDX-FileCopyrightText: 2021 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""
Blink example for boards with ONLY a NeoPixel LED (e.g. without a built-in red LED).
Includes QT Py and various Trinkeys.

Requires two libraries from the Adafruit CircuitPython Library Bundle.
Download the bundle from circuitpython.org/libraries and copy the
following files to your CIRCUITPY/lib folder:
* neopixel.mpy
* adafruit_pixelbuf.mpy

Once the libraries are copied, save this file as code.py to your CIRCUITPY
drive to run it.
"""

import time
import board
import digitalio
import neopixel


# Simple LED
led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

# RGD LED
with neopixel.NeoPixel(board.NEOPIXEL, 1) as pixel:
    pixel.brightness = 0.3

    while True:
        led.value = True
  
        pixel.fill((255, 0, 0))
        time.sleep(0.5)
        pixel.fill((0, 255, 0))
        time.sleep(0.5)
        pixel.fill((0, 0, 255))
        time.sleep(0.5)

        led.value = False
        pixel.fill(0)
        pixel.show() 
        time.sleep(5)
