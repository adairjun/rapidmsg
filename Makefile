# # Use 'make V=1' to see the full commands
#使用安静模式可以不看gcc,g++的参数
CC := gcc 
CXX := g++

CPPFLAGS := -std=c++0x -O2 -g -fPIC

PROTOFILES := $(wildcard ./proto/*.proto)
HEADERS := $(addsuffix .pb.h, $(notdir $(basename $(PROTOFILES))))
CPPFILES := $(addsuffix .pb.cc, $(notdir $(basename $(PROTOFILES))))
OBJECTS := $(addsuffix .pb.o, $(notdir $(basename $(PROTOFILES))))
TARGET := libmessage.so

ifeq ("$(origin V)", "command line")
   BUILD_VERBOSE = $(V)
endif
ifndef BUILD_VERBOSE
   BUILD_VERBOSE = 0
endif

ifeq ($(BUILD_VERBOSE),0)
	QUIET_CC        = @echo '   ' CC $@;
	QUIET_CXX       = @echo '   ' CXX $@;
	QUIET_LINK      = @echo '   ' LINK $@;
endif

all:$(TARGET)
	cp $(HEADERS) include/
	@echo "--------------------------make successful-----------------------"

$(TARGET):$(OBJECTS)
	$(QUIET_LINK)$(CXX) -shared -fPIC -o ./lib/$(TARGET) $^

%.pb.o:%.pb.cc
	$(QUIET_CXX)$(CXX) $(CPPFLAGS) -o $@ -c $<

%.pb.cc:./proto/%.proto
	protoc --proto_path=./proto --cpp_out . $<

.PHONY:clean show
# ./include下的头文件和./lib下的库文件不要删除
clean:
	-rm -f $(OBJECTS) $(CPPFILES) $(HEADERS) 
	@echo "----------------------------make clean-----------------------"

#这是用来调试Makefile用的
show:
	@echo "PROTOFILES"
	@echo $(PROTOFILES)
	@echo "-------------------------------------------"
	@echo "HEADERS"
	@echo $(HEADERS)
	@echo "-------------------------------------------"
	@echo "CPPFILES"
	@echo $(CPPFILES)
	@echo "-------------------------------------------"
	@echo "OBJECTS"
	@echo $(OBJECTS)
	@echo "-------------------------------------------"
