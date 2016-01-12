# # Use 'make V=1' to see the full commands
#使用安静模式可以不看gcc,g++的参数
CC := gcc 
CXX := g++

CPPFLAGS := -std=c++0x -O2 -g -fPIC

PROTOFILES := $(wildcard ./proto/*.proto)
PROTOHEADERS := $(addsuffix .pb.h, $(notdir $(basename $(PROTOFILES))))
PROTOCPPFILES := $(addsuffix .pb.cc, $(notdir $(basename $(PROTOFILES))))
PROTOOBJECTS := $(addsuffix .pb.o, $(notdir $(basename $(PROTOFILES))))

LIBCFILES := $(wildcard ./util/*.c)
LIBCPPFILES := $(wildcard ./util/*.cc ./util/*.cpp)
LIBOBJECTS := $(addsuffix .o, $(basename $(LIBCFILES)) $(basename $(LIBCPPFILES)))

INCLUDE := -I/usr/local/include -I./include
LIBS := -L/usr/local/lib -lprotobuf
TARGET := librapidmsg.so

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
	cp $(PROTOHEADERS) include/rapidmsg/
	@echo "--------------------------make successful-----------------------"

$(TARGET):$(PROTOOBJECTS) $(LIBOBJECTS)
	$(QUIET_LINK)$(CXX) -shared -fPIC -o $(TARGET) $^ $(LIBS)

%.pb.o:%.pb.cc
	$(QUIET_CXX)$(CXX) $(CPPFLAGS) -o $@ -c $<

%.pb.cc:./proto/%.proto
	protoc --proto_path=./proto --cpp_out . $<

./util/%.o:./util/%.c
	$(QUIET_CC)$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

./util/%.o:./util/%.cc
	$(QUIET_CXX)$(CXX) $(INCLUDE) $(CPPFLAGS) -c -o $@ $<

./util/%.o:./util/%.cpp 
	$(QUIET_CXX)$(CXX) $(INCLUDE) $(CPPFLAGS) -c -o $@ $<

.PHONY:clean show
# ./include下的头文件和./lib下的库文件不要删除
clean:
	-rm -f $(TARGET) $(PROTOOBJECTS) $(PROTOCPPFILES) $(PROTOHEADERS)  $(LIBOBJECTS)
	@echo "----------------------------make clean-----------------------"

#这是用来调试Makefile用的
show:
	@echo "PROTOFILES"
	@echo $(PROTOFILES)
	@echo "-------------------------------------------"
	@echo "PROTOHEADERS"
	@echo $(PROTOHEADERS)
	@echo "-------------------------------------------"
	@echo "PROTOCPPFILES"
	@echo $(PROTOCPPFILES)
	@echo "-------------------------------------------"
	@echo "PROTOOBJECTS"
	@echo $(PROTOOBJECTS)
	@echo "-------------------------------------------"

install:
	cp -r ./include/rapidmsg /usr/local/include
	cp $(TARGET) /usr/local/lib 
