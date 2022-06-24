CC = gcc
CXX = g++

src := $(wildcard *.c) $(wildcard *.cpp)
dir = $(notdir $(src))
obj := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(dir)))

target = print_reg channel_probe

all: $(target)
	@echo $(src)
	@echo $(dir)
	@echo $(obj)

print_reg: print_reg.o $(filter-out print_reg.o channel_probe.o, $(obj))
	$(CC) -o $@ $^
channel_probe: channel_probe.o $(filter-out print_reg.o channel_probe.o, $(obj))
	$(CC) -o $@ $^


%.o : %.c
	$(CC) -c -std=c99 $^ -o $@
%.o : %.cpp
	$(CXX) -c $^ -o $@  

.PHONY: clean
clean:
	rm $(obj) $(target) -f

