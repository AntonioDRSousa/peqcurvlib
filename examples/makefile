all:
	gcc -std=c17 main.c peqcurvlib\curves.c peqcurvlib\sdltools.c -I SDL2\SDL2\include -L SDL2\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main
	.\main
	
clean:
	rm *.exe