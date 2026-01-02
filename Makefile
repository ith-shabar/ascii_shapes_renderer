CC = gcc
CFLAGS = -Wall -g
CLINK = -lm

SOURCE = main.c 
OBJECT = $(SOURCE:.c=.o)
EXECUTABLE = program

default: $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECT)
	$(CC) $(CFLAGS) $(CLINK) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean: 
	rm -rf $(OBJECT)

delete: 
	rm $(EXECUTABLE)
