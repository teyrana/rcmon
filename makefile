MAIN=revmon

# ===================================================
default:build

clean:
	rm -rf build/*

.PHONY:config
config: build/CMakeCache.txt

build/CMakeCache.txt:
	cd build && cmake ..

build/${MAIN}.uf2: build

.PHONY:build
build: build/CMakeCache.txt $(SRCS)
	cd build && make

.PHONY:mon
mon: 
	stty -F /dev/ttyACM0 115200
	screen /dev/ttyACM0 

reboot:reset

.PHONY:reset
reset:
	$(eval ADDR:=$(shell lsusb | grep Pico | cut -c16-18))
	@echo ":> Rebooting device at Address:${ADDR}"
	picotool reboot --usb --bus 3 --address ${ADDR} --force
	sleep 3

.PHONY:run
run: reboot upload

.PHONY:upload
upload: build/${MAIN}.uf2
	cp build/${MAIN}.uf2 /media/teyrana/RPI-RP2/
	sleep 2

deploy-scan:
	cp tools/i2c-scan.py /media/$USER/CIRCUITPY/main.py

deploy-ping:
	cp tools/i2c-ping.py /media/${USER}/CIRCUITPY/main.py

deploy-blink-feather:
	cp tools/feather-rp2040-blink.py /media/$USER/CIRCUITPY/main.py

deploy-blink-one:
	cp tools/rp2040-one-blink.py /media/$USER/CIRCUITPY/main.py

	