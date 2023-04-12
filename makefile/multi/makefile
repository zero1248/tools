CC = gcc
CXX = g++
#CXXSTD = -std=c++17
CSTD = -std=c99
#LDFLAGES = -lhdf5_cpp -lhdf5 -lpthread -lz
#CFLAGS = -Wall -O2
#INCLUDE = -I./
#LIB = -L/usr/local/hdf5/lib

src := $(wildcard *.c) $(wildcard *.cpp)
dir = $(notdir $(src))
obj := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(dir)))

target = print_reg channel_probe
target_o = $(addsuffix .o, $(target))

all: $(target)
	@echo $(src)
	@echo $(dir)
	@echo $(obj)

print_reg: print_reg.o $(filter-out $(target_o), $(obj))
	$(CC) -o $@ $^
channel_probe: channel_probe.o $(filter-out $(target_o), $(obj))
	$(CC) -o $@ $^


%.o : %.c
	$(CC) -c $(CSTD) $^ -o $@
%.o : %.cpp
	$(CXX) -c $^ -o $@  

.PHONY: clean
clean:
	rm $(obj) $(target) -f

