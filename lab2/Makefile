.PHONY: build

build: clean
	mkdir build
	cd ./build; cmake ..; cmake --build .

run: build
	./build/*_exe $(threads)

clean:
	rm -rf ./build/

strace: build
	strace -f ./build/*_exe $(threads)

gen-data:
	python3 ./generator/generator.py

show-stat:
	python3 ./analytics/create_graphic.py