TARGET = game

SHELL = /bin/sh

BUILD_DIR = $(shell pwd)
SRC_DIR = $(BUILD_DIR)/../src
LIB_DIR= $(BUILD_DIR)/../lib

LUA = $(LIB_DIR)/lua-5.2.4
LUABRIDGE = $(LIB_DIR)/luaBridge

CXX = g++ -std=c++11
CXXFLAGS = -g -Wall
CPPFLAGS = -I/usr/local/include

SRCS = $(wildcard $(SRC_DIR)/*.cxx)
LIBS = -llua 
INCLUDES = $(wildcard $(SRC_DIR)/*/*.hxx)
OBJS = $(notdir $(SRCS:.cxx=.o))

LDFLAGS = -L$(LIB_DIR) -L$(LUA)/src
IPATH = -I../src -I../lib -I$(LUA)/src -I$(LUABRIDGE)

$(TARGET) : $(OBJS) .depend
	$(CXX) $(OBJS) $(CXXFLAGS) $(IPATH) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o :
	$(CXX) $(IPATH) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@



# include-file dependency information
#
.depend:	$(SRCS) $(INCLUDES)
	- $(CXX) -MM $(SRCS) > .depend

ifneq ($(MAKECMDGOALS),clean)
sinclude .depend
endif

# cleanup by removing generated files
#
.PHONY:		clean
clean:
		rm -rf *.o $(TARGET)

print-%: 
	@echo $* = $($*)