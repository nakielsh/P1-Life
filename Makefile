main:
	$(CC) -o build/life main.c fileio.c pngout.c life.c -lm -lpng
	