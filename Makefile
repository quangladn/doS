
build: src/doS.cpp
	g++ src/doS.cpp -o build/Termux/doS
build-windows: src/doS.cpp
	windres src/recource.rc -O coff -o build/Windows/re.res
	g++ src/doS.cpp -o  build/Windows/doS build/Windows/re.res
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
