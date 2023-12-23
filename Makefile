all: ./bin/scanner.bin

./bin/scanner.bin: ./src/scanner/main.c ./build/scanner/scanner.c
	gcc -I./src/scanner -o ./bin/scanner.bin ./src/scanner/main.c ./build/scanner/scanner.c

./build/scanner/scanner.c: ./src/scanner/scanner.flex
	flex -o ./build/scanner/scanner.c ./src/scanner/scanner.flex 

clean:
	rm -f ./bin/*.bin
	rm -f ./build/scanner/*.o
	rm -f ./build/scanner/*.c


