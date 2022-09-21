
build: src/doS.cpp
	g++ src/doS.cpp -o build/Termux/doS
install-linux-build:
	make build_
	cp build/doS usr/local/bin/doS
install-unix-build:
	make build_
	cp build/doS ~/../usr/bin/doS
install-linux:
	cp build/doS usr/local/bin/doS
install-unix:
	cp build/doS ~/../usr/bin/doS
