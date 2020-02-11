CC = gcc
CFLAGS := -g  -Wall  -I../header 
SRCS = $(wildcard ./*.c)
EXEC= app
CPPFLAGS:= -I../header -lpthread 
OBJS = $(patsubst ./%.c,../obj/%.o,$(SRCS))

$(EXEC):$(OBJS)
	$(CC) $^  -o $@ -lunp 

../obj/%.o:%.c
	$(CC)  $(CPPFLAGS) -c $< -o $@ $(CFLAGS) 

.PHONY : clean
clean:
	rm -rvf ../obj/$(OBJS) $(EXEC)
