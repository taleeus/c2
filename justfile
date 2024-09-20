default: build

rebuild:
    @premake5 gmake && make clean && bear -- make

build:
    @make

build-release:
    @make release

test:
    @make config=test
    @bin/Test/test/c2-test
