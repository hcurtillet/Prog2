CFLAGS= -c -g  -Wall


mainProg : algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o  main.o
	clang  algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o main.o -o mainProg

testAlgoProg : algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_algo.o
	clang algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_algo.o -o testAlgoProg

testCheminsProg : algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_chemins.o
	clang algo.o graphe_lecture.o fifo_list.o heap.o parcours_stations.o chemins.o test_chemins.o -o testCheminsProg


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


graphic_mode.o : graphic_mode.c
	clang $(LDFLAGS) graphic_mode.c

clean:
	rm -f *.o
