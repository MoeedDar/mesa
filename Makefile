TARGET = mesa

.PHONY: all clean run

all: build

build:
	cmake -GNinja -B./build -H.

$(TARGET): build
	cd build && cmake --build .

run: mesa
	bin\$(TARGET)

clean:
	rm -rf build
