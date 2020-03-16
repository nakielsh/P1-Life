main:
	$(CC) -o build/life main.c fileio.c pngout.c life.c friends.c generate.c pathutils.c helperr.c -lm -lpng -ggdb
	