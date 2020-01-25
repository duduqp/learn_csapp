CC = gcc
CFLAGS := -g  -Wall 
SRCS = $(wildcard ./*.c)
EXEC= app
CPPFLAGS:= -I../header -lpthread
OBJS = $(patsubst ./%.c,../obj/%.o,$(SRCS))

$(EXEC):$(OBJS)
	$(CC) $^  -o $@

../obj/%.o:%.c
	$(CC)  $(CPPFLAGS) -c $< -o $@ $(CFLAGS) 

.PHONY : clean
clean:
	rm -rvf ../obj/$(OBJS) $(EXEC)
