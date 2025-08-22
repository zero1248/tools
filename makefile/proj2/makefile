# CC = gcc
# # CXX = g++

# src := $(wildcard *.c) $(wildcard src/*.c)
# dir = $(notdir $(src))
# obj := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(dir)))
# CFLAGS += -I./inc 


# target = xdma_reg_info xdma_ch_info xdma_reg_rw
# target_o = $(addsuffix .o, $(target))

# all: $(target)
# 	@echo $(src)
# 	@echo $(dir)
# 	@echo $(obj)

# xdma_reg_info : xdma_reg_info.o $(filter-out $(target_o), $(obj))
# 	$(CC) -o $@ $^ $(CFLAGS)
# xdma_ch_info : xdma_ch_info.o $(filter-out $(target_o), $(obj))
# 	$(CC) -o $@ $^ $(CFLAGS)
# xdma_reg_rw : xdma_reg_rw.o $(filter-out $(target_o), $(obj))
# 	$(CC) -o $@ $^ $(CFLAGS)

# %.o : %.c
# 	$(CC) -c -std=c11 $^ -o $@
# # %.o : %.cpp
# # 	$(CXX) -c $^ -o $@  

# .PHONY: clean
# clean:
# 	rm $(obj) $(target) -f

# 顶层目录
PROJECT_DIR := $(abspath .)
SRC_DIR     := $(PROJECT_DIR)/src
INC_DIR     := $(PROJECT_DIR)/inc
APP_DIR     := $(PROJECT_DIR)/app
BUILD_DIR   := $(PROJECT_DIR)/build

# 编译器与参数
CC      := gcc
CFLAGS  := -I$(INC_DIR) -I$(APP_DIR) -O2
CFLAGS  += -Wall -Wextra

# 创建构建目录（用于 .o 文件）
$(shell mkdir -p $(BUILD_DIR))

# 所有基础源文件
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS  := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# 所有可执行主文件（app/下的每个 .c 文件 -> 可执行文件）
APP_SRCS  := $(wildcard $(APP_DIR)/*.c)
APP_BINS  := $(patsubst $(APP_DIR)/%.c, %, $(APP_SRCS))

# 默认目标：构建所有可执行文件
all: $(APP_BINS)

# 编译每个可执行文件
%: $(APP_DIR)/%.c $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

# 编译基础模块（src 下）
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(BUILD_DIR)/*.o $(APP_BINS)

.PHONY: all clean


