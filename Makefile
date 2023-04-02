dev:
		pio run

simu:	dev
	cd .pio/build/simu && ./program

build:
	pio run -e esp32

upload: build load

load:
	sudo /home/gtoubol/.platformio/penv/bin/pio run -e esp32 -t upload

monitor:
	sudo /home/gtoubol/.platformio/penv/bin/pio run -e esp32 -t monitor
