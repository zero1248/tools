SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')
CUR_SOURCE=$(wildcard *.c) $(wildcard *.cpp)
CUR_OBJS=$(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(CUR_SOURCE)))

all : $(SUBDIRS) $(CUR_OBJS)
$(SUBDIRS) : ECHO
	make -C $@
$(CUR_OBJS) : %.o:%.cpp
	$(CC) -c $(INC) $^ -o $(ROOT_DIR)/$@
ECHO:
	@echo $(SUBDIRS)