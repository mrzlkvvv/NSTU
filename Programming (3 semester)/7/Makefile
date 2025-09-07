.SILENT:

run: build
	./bin/main

build:
	gcc main.c -o ./bin/main

clean:
	rm -rf ./bin/

format:
	clang-format --style=Microsoft -i ./main.c
