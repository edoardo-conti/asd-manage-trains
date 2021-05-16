CC = gcc
CFLAGS = -ansi -Wall

main: asd_manage_trains.c asd_manage_trains_lib.c
	${CC} ${CFLAGS} -o main asd_manage_trains.c asd_manage_trains_lib.c

clean:
	rm -f main
