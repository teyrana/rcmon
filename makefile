MAIN=i2c_scan
PICOTOOL=~/project/picotool/build/picotool 

# ===================================================
default:build

clean:
	rm -rf build/*

.PHONY:config
config: build/CMakeCache.txt

build/CMakeCache.txt:
	cd build && cmake .. -GNinja

build/${MAIN}.uf2: build

.PHONY:build
build: build/CMakeCache.txt $(SRCS)
	cd build && ninja

.PHONY:mon
mon: build/revmon

build/revmon:
	cd build && ninja revmon

.PHONY: blink
blink: build/src/blink/blink.uf2

build/src/blink/blink.uf2:
	cd build && ninja blink

.PHONY: scan
scan: build/src/scan/i2c_scan

build/src/scan/i2c_scan:
	cd build && ninja i2c_scan

.PHONY: connect
connect:
	stty -F /dev/ttyACM0 115200
	screen /dev/ttyACM0 

reboot:reset

.PHONY:reset
reset:
	$(eval ADDR:=$(shell lsusb | grep 'Raspberry Pi RP' | cut -c16-18))
	@echo ":> Rebooting device at Address:${ADDR}"
	${PICOTOOL} reboot --usb --bus 3 --address ${ADDR} --force
	sleep 3

.PHONY:run
run: reboot upload

.PHONY:upload
upload: build/${MAIN}.uf2
	cp build/${MAIN}.uf2 /media/${USER}/RPI-RP2/
	sleep 2

.PHONY:upload
upload-blink: build/src/blink/blink.uf2
	cp build/src/blink/blink.uf2 /media/${USER}/RPI-RP2/
	sleep 2

.PHONY:upload
upload-scan: build/scan.uf2
	cp build/scan.uf2 /media/${USER}/RPI-RP2/
	sleep 2

# circuitpy-setup:
# 	mkdir -p /media/${USER}/CIRCUITPY/lib/
# 	unzip extern/adafruit-circuitpython-bundle-*zip  -d extern/
#   cp -r extern/adafruit-circuitpython-bundle-9.x-mpy-20240503/lib/* /media/${USER}/CIRCUITPY/lib/

deploy-scan:
	cp tools/i2c-scan.py /media/${USER}/CIRCUITPY/code.py

deploy-ping:
	cp tools/i2c-ping.py /media/${USER}/CIRCUITPY/code.py

deploy-blink: deploy-blink-feather

deploy-blink-feather:
	cp tools/feather-rp2040-blink.py /media/${USER}/CIRCUITPY/code.py

deploy-blink-rpi-pico:
	cp tools/rpi-pico-blink.py /media/${USER}/CIRCUITPY/code.py

