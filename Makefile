dev:
		pio run

simu:	dev
	cd .pio/build/simu && ./program
		