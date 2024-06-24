#makefile

CC=gcc
LD=gcc
CCFLAGS1=-std=c99 -pedantic -Wall
CCFLAGS2=-lm
FINAL=prog.out
OBJ0=main.c queue_tok_list_functions.c tree_tok_bin_functions.c stack_tree_list_functions.c stack_tok_list_fucntions.c
OBJ=$(OBJ0:.c=.o)


$(FINAL): $(OBJ)
	$(LD) $(OBJ) -o $(FINAL) $(CCFLAGS2)

.c.o:
	$(CC) $(CCFLAGS1) -c $< -o $@

main.o: enums_and_structs.h

queue_tok_list_functions.o: queue_tok_list.h enums_and_structs.h

tree_tok_bin_functions.o: tree_tok_bin.h enums_and_structs.h

stack_tree_list_functions.o: stack_tree_list.h enums_and_structs.h

stack_tok_list_fucntions.o: stack_tok_list.h enums_and_structs.h enum_for_stack_of_trees.h

clean:
	rm -f *.o
