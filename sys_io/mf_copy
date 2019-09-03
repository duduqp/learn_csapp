CC = gcc
CFLAGS := -g -Wall -I./ -L./
EXEC=app
SRCS = $(wildcard ./*.c)
OBJS = $(patsubst ./%.c,./%.o,$(SRCS))

$(EXEC):$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@

.PHONY : clean
clean:
	rm -rvf $(OBJS) $(EXEC)
