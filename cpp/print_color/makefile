src = $(wildcard *.c) $(wildcard *.cpp)
obj = $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(src)))

target = pc
CC = g++

$(target):$(obj)
	$(CC) $^ -o $@


%.o:%.c
	$(CC) -c $< -o $@

.PHOINY:clean
clean:
	rm -f *.o
	rm -f *.so
	rm -f ${target}

