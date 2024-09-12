project := "c2"
executable := "bin" / "Debug" / project

default: build

rebuild:
    @premake5 gmake && make clean && bear -- make

build:
    @make
