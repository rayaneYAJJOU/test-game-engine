all:
	gcc -o main main.c source/color.c source/def.c source/input.c source/matrix.c source/quaternion.c source/renderer.c source/timer.c source/vector3.c source/window.c -lmingw32 -lSDL2main -lSDL2