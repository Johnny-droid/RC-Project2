SRC = src/

make:
	rm -f download
	gcc -Wall main.c $(SRC)/*.c include/macros.h -o download