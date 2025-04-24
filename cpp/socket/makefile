CC = gcc
CXX = g++
CXXSTD = -std=c++11
# CSTD = -std=c99
#LDFLAGS = -lhdf5_cpp -lhdf5 -lpthread -lz
LDFLAGS = -lpthread
#CFLAGS = -Wall -O2
INCLUDE = -I./
#LIB = -L/usr/local/hdf5/lib

src := $(wildcard *.c) $(wildcard *.cpp)
dir = $(notdir $(src))
obj := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(dir)))

target = socket_recv socket_send test_UDPReceiver
target_o = $(addsuffix .o, $(target))

all: $(target)
	@echo $(src)
	@echo $(dir)
	@echo $(obj)

socket_recv: socket_recv.o $(filter-out $(target_o), $(obj))
	$(CXX) -o $@ $^
socket_send: socket_send.o $(filter-out $(target_o), $(obj))
	$(CXX) -o $@ $^
test_UDPReceiver: test_UDPReceiver.o $(filter-out $(target_o), $(obj))
	$(CXX) -o $@ $^

%.o : %.cpp
	$(CXX) -c $(CXXSTD) $^ -o $@  

.PHONY: clean print
clean:
	rm $(obj) $(target) -f

print:
	@echo "src: " $(src)
	@echo "obj: " $(obj)
# @echo "src: " $(src)

