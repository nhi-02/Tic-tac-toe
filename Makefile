all:
	g++ -I D:/VJU/sdl2/dev/SDL2/include  -L D:/VJU/sdl2/dev/SDL2/lib  -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	gcc -I D:/VJU/sdl2/dev/SDL2/include  -L D:/VJU/sdl2/dev/SDL2/lib  -o openicon openicon.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
clean:
	del main.exe