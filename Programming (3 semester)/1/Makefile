.SILENT:

run_and_clean:
	mkdir ./bin/
	gcc main.c -o ./bin/main
	./bin/main test.txt 5
	rm -rf ./bin/

format:
	clang-format -i ./main.c
