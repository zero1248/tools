BIN = ./bin
SRC = ./src
OBJ = ./obj
INC = ./include

SRCS = $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst %.c, $(OBJ)/%.o, $(patsubst %.cpp, $(OBJ)/%.o, $(notdir $(SRCS))))


TARGET_NAME = main
TARGET_PATH = $(BIN)/$(TARGET_NAME)

ifeq ($(OS), Windows_NT)
	RM = del
	RM_TARGET_PATH = .\bin\$(TARGET_NAME).exe
	RM_OBJ_PATH = .\obj\*.o
else
	RM = rm -f
	RM_TARGET_PATH = $(BIN)/$(TARGET_NAME)
	RM_OBJ_PATH = $(OBJ)/*.o
endif

G++ = g++
GCC = gcc

# Compile
# CFLAGS = -I$(INC)
# debug
CFLAGS = -g -Wall -I$(INC)

$(TARGET_PATH):$(OBJS)
	$(G++) $^ -o $@

$(OBJ)/%.o:$(SRC)/%.cpp
	$(G++) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o:$(SRC)/%.c
	$(GCC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:	
	$(RM) $(RM_TARGET_PATH) $(RM_OBJ_PATH)