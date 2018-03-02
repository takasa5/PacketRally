all: master player

master: message.h master.c
	gcc master.c -o master

player: message.h player.c
	gcc player.c -o player