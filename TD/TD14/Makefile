DIRSDL=/usr/local
CFLAGS= -c -g  -I$(DIRSDL)/include  -Wall
LDFLAGS= -lSDL2 -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_phelma -lm

EXE=test_exp1 test_exp2 test_exp3 test_exp4 test_exp5 monProgramme
EXE_FILE=test_exp1_file test_exp2_file test_exp3_file test_exp4_file test_exp5_file
OBJ=element.o expression.o binarytree.o expressionplot.o
OBJ_FILE=element.o expression.o binarytree.o expressionsave.o

graphique : $(EXE)
texte:$(EXE_FILE)

monProgramme : $(OBJ) monProgramme.o
	gcc -o $@ $^ $(LDFLAGS)

test_exp5 :$(OBJ) test_exp5.o analyse.o
	gcc -o $@ $^ $(LDFLAGS)

test_exp5_file : $(OBJ_FILE) test_exp5_file.o analyse.o
		gcc -o $@ $^

test_exp4 : $(OBJ) test_exp4.o analyse.o
	gcc -o $@ $^ $(LDFLAGS)

test_exp4_file : $(OBJ_FILE) test_exp4_file.o analyse.o
		gcc -o $@ $^

test_exp3 : $(OBJ) test_exp3.o
	gcc -o $@ $^ $(LDFLAGS)

test_exp3_file : $(OBJ_FILE) test_exp3_file.o
	gcc -o $@ $^

test_exp2 : $(OBJ) test_exp2.o
	gcc -o $@ $^ $(LDFLAGS)

test_exp2_file : $(OBJ_FILE) test_exp2_file.o
	gcc -o $@ $^

test_exp1 : $(OBJ) test_exp1.o
	gcc -o $@ $^ $(LDFLAGS)

test_exp1_file : $(OBJ_FILE) test_exp1_file.o
	gcc -o $@ $^

%.o	:%.c
	gcc  $< $(CFLAGS)

clean:
		rm -f *.o $(EXE) $(EXE_FILE)
