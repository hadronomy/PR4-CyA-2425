PROJECT_NAME = PR4-CYA-2223

cmake:
	cmake -S . -B build

build: cmake
	cd build; make

clean:
	rm -rf build

tar:
	tar cvfz HernándezJiménezPablo-$(PROJECT_NAME).tar.gz --exclude-from=.gitignore ./*
