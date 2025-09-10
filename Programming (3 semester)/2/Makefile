.SILENT:

run_and_clean:
	mkdir ./bin
	gcc -fPIC -shared -o ./bin/fileprocessor.so ./src/fileprocessor.c
	gcc ./src/main.c -o ./bin/main
	./bin/main test.txt 5
	rm -rf ./bin/

format:
	clang-format -i ./src/*
