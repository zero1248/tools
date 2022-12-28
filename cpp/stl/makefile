CC = gcc
CXX = g++

src := $(wildcard *.c) $(wildcard *.cpp)
dir = $(notdir $(src))
obj := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(dir)))

target = vector_test deque_test

all: $(target)
	@echo $(src)
	@echo $(dir)
	@echo $(obj)

vector_test: vector_test.o $(filter-out vector_test.o deque_test.o, $(obj))
	$(CXX) -o $@ $^
deque_test: deque_test.o $(filter-out vector_test.o deque_test.o, $(obj))
	$(CXX) -o $@ $^


%.o : %.c
	$(CC) -c -std=c99 $^ -o $@
%.o : %.cpp
	$(CXX) -c $^ -o $@  

.PHONY: clean
clean:
	rm $(obj) $(target) -f

