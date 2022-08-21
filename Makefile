run:
	g++ src/doS.cpp -o build/doS
install-linux:
	make
	cp build/doS usr/local/bin/doS
install-unix:
	make
	cp build/doS ~/../usr/bin/doS
