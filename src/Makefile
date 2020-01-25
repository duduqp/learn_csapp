CC = gcc
CFLAGS := -g  -Wall 
EXEC=main
CPPFLAGS:= -I../header -lpthread
SRCS = $(wildcard ./*.c)
OBJS = $(patsubst ./%.c,../obj/%.o,$(SRCS))

$(EXEC):$(OBJS)
	$(CC) $^  -o $@

../obj/%.o:%.c
	$(CC)  $(CPPFLAGS) -c $< -o ../obj/$@ $(CFLAGS) 

.PHONY : clean
clean:
	rm -rvf ../obj/$(OBJS) $(EXEC)
