DIRSDL=/users/prog1a/C/librairie/SDL2_Phelma

CFLAGS= -c -g  -I$(DIRSDL)/include  -Wall
LDFLAGS= -L$(DIRSDL)/lib -lSDL2 -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_phelma -lm -lSDL_sound


mainProg : algo.o graphe_lecture.o fifo_list.o main.o
	clang $(LDFLAGS) algo.o graphe_lecture.o fifo_list.o main.o -o mainProg

main.o : main.c
	clang $(CFLAGS) main.c

algo.o : algo.c
	clang $(CFLAGS) algo.c

graphe_lecture.o : graphe_lecture.c
	clang $(CFLAGS) graphe_lecture.c

fifo_list.o : fifo_list.c
	clang $(CFLAGS) fifo_list.c


clean:
	rm -f *.o fifo_list main algo graphe_lecture mainProg
