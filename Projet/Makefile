DIRSDL=/users/prog1a/C/librairie/SDL2_Phelma

CFLAGS= -c -g  -I$(DIRSDL)/include  -Wall
LDFLAGS= -L$(DIRSDL)/lib -lSDL2 -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_phelma -lm -lSDL_sound


mainProg : algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o  main.o
	clang $(LDFLAGS) algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o main.o -o mainProg

testAlgoProg : algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_algo.o
	clang $(LDFLAGS) algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_algo.o -o testAlgoProg

testCheminsProg : algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_chemins.o
	clang $(LDFLAGS) algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_chemins.o -o testCheminsProg

main.o : main.c
	clang $(CFLAGS) main.c

algo.o : algo.c
	clang $(CFLAGS) algo.c

chemins.o : chemins.c
	clang $(CFLAGS) chemins.c

graphe_lecture.o : graphe_lecture.c
	clang $(CFLAGS) graphe_lecture.c

fifo_list.o : fifo_list.c
	clang $(CFLAGS) fifo_list.c

heap.o : heap.c
	clang $(CFLAGS) heap.c

parcours_stations.o : parcours_stations.c
	clang $(CFLAGS) parcours_stations.c

test_algo.o : test_algo.c
	clang $(CFLAGS) test_algo.c

test_chemins.o : test_chemins.c
	clang $(CFLAGS) test_chemins.c

lab.o : Lab.c
	clang $(LDFLAGS) Lab.c

clean:
	rm -f *.o fifo_list main algo graphe_lecture mainProg heap parcours_stations
