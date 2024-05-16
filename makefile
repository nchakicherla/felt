CC = gcc
CFLAGS = -std=c99 -Wall -Wpedantic -Werror -luuid
OS := $(shell uname)

mkBinDir := $(shell mkdir -p bin)
mkObjDir := $(shell mkdir -p obj)


MAIN = 	./obj/main.o

OBJS = 	./obj/pm_memory.o		\
		./obj/pm_error.o 		\
		./obj/pm_string.o 		\
		./obj/pm_interpreter.o 	\
		./obj/pm_file.o 		\
		./obj/pm_db.o 			\

final-run: final-link
ifeq ($(OS),Darwin) 
		./bin/practice.run
else 
		valgrind --track-origins=yes ./bin/practice.run  
endif

final-link: $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN) -o ./bin/practice.run

./obj/%.o: ./src/%.c ./src/%.h ./src/pm_common.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o ./obj/main.o
clean: obj-clean
	trash-put ./bin/*

obj-clean:
	trash-put ./obj/*
