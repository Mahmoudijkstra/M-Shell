CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJS = main.o parser.o executor.o builtins.o

myshell: $(OBJS)
	$(CC) $(CFLAGS) -o myshell $(OBJS)

main.o: main.c parser.h executor.h builtins.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

executor.o: executor.c executor.h
	$(CC) $(CFLAGS) -c executor.c

builtins.o: builtins.c builtins.h
	$(CC) $(CFLAGS) -c builtins.c

clean:
	rm -f *.o myshell
