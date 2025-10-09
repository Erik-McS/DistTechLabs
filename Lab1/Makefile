.PHONY: all

all : heat future async

future : future_starter.c
	gcc -W -Wall -g -ggdb -o $@ -lpthread $<

async : async_starter.c
	gcc -W -Wall -g -ggdb -o $@ -lpthread $<

heat : heat.c
	gcc -W -Wall -g -ggdb -o $@ -lpthread -lm $<