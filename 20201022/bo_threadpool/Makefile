INC_DIR :=  ./
SRC_DIR = ./
#EXE_DIR := ./bin
CC := g++
CPPFLAGS := -g
LIBS := -lpthread
INC_FILE := $(addprefix -I, $(INC_DIR))
CPP_FILE :=  $(wildcard ./*.cc) 
OBJS := $(patsubst %.cc, %.o, $(CPP_FILE))
objs:=$(addsuffix /*.o, $(SRC_DIR))
TARGET := threadpool.exe
$(TARGET):$(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(INC_FILE) $(LIBS)
%.o:%.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $< $(INC_FILE) $(LIBS)
object:
	@echo $(OBJS)
clean:
	rm -rf $(TARGET) $(OBJS)
