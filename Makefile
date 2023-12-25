all: ./bin/scanner.bin ./bin/parser.bin

./bin/scanner.bin: ./src/scanner/main.c ./build/scanner/scanner.c
	gcc -I./src -I./src/scanner -g -o ./bin/scanner.bin ./src/scanner/main.c ./build/scanner/scanner.c

./bin/parser.bin: ./src/parser/main.c
	gcc -I./src -I./src/parser -g -o ./bin/parser.bin ./src/parser/main.c 

./build/scanner/scanner.c: ./src/scanner/scanner.flex
	flex -o ./build/scanner/scanner.c ./src/scanner/scanner.flex 

clean:
	rm -f ./bin/*.bin
	rm -f ./build/scanner/*.o
	rm -f ./build/scanner/*.c


