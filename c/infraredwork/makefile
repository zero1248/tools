src = $(wildcard *.c) $(wildcard *.cpp)
obj = $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(src)))

target = blackbody
CC = gcc

$(target):$(obj)
	$(CC) $^ -o $@ -lm


%.o:%.c
	$(CC) -c $< -o $@

.PHOINY:clean
clean:
	rm -f *.o
	rm -f *.so
	rm -f ${target}

