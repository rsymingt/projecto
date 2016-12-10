all: clear projecto run

projecto: src/main.c src/avl.c src/commands.c src/filehandling.c src/linkedlist.c
	gcc src/main.c src/avl.c src/commands.c src/filehandling.c src/linkedlist.c -Wall -Ilibraries -std=c99 -o projecto
	
run:
	./projecto
	
clean:
	rm projecto
	
clear:
	clear
