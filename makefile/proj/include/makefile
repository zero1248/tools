# 子目录的 makefile 直接读取其子目录
SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')
# 以下同根目录下的 makefile 的相同代码的解释
CUR_SOURCE=${wildcard *.c}
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}

all : $(SUBDIRS) $(CUR_OBJS)
$(SUBDIRS) : ECHO
	make -C $@
$(CUR_OBJS) : %.o:%.c
	$(CC) -c $(INC) $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@
ECHO:
	@echo $(SUBDIRS)