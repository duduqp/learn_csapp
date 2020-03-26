INCLUDE := -I$(HOME)/csapp/include
DEFINES := 
SOURCE :=$(wildcard *.c) $(wildcard *.cpp)
OBJS :=$(patsubst %.c,&.o,$(patsubst %.cpp,%.o,$(SOURCE)))
LDFLAGS :=
LIBS :=
#to generate dynamic lib.so
#SHARE := -fPIC -shared -o

#your application name
APP := main
CC := g++#append g++
#use for c
CFLAGS := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS  := $(CFLAGS) 
.PHONY: cleanall buildall all objs cleanobj rebuild 

cleanall:
	rm -rf $(OBJS) $(APP)
buildall:$(APP)

all: $(APP)

objs:$(OBJS)

cleanobj:
	rm -fr $(wildcard *.o)
rebuild:
	cleanall buildall

$(APP) : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
