.PHONY: all

all : heat future async heatParallel

future : future_starter.c
	gcc -W -Wall -g -ggdb -o $@ -lpthread $<

async : async_starter.c
	gcc -W -Wall -g -ggdb -o $@ -lpthread $<

heat : heat.c
	gcc -W -Wall -g -ggdb -o $@ -lpthread -lm $<

heatParallel : heatParallel.c
	gcc -W -Wall -g -ggdb -o $@ -lpthread -lm $<

