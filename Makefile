CC = gcc
CFLAGS := -g -Wall  -I./ -L./ 
EXEC=main
SRCS = $(wildcard ./*.c)
OBJS = $(patsubst ./%.c,./%.o,$(SRCS))

$(EXEC):$(OBJS)
	$(CC) $^  -o $@

%.o:%.c
	$(CC) -c $< -o $@ -Wall -lpthread -I/home/ddqp/csapp/header

.PHONY : clean
clean:
	rm -rvf $(OBJS) $(EXEC)
