# name of the library
LIBNAME = Knives

#Necessary to use shell built-in commands
SHELL = bash

# A list of directories
BASE_DIR = $(shell pwd)
LIB_DIR  = ../lib
EXE_DIR  = $(BASE_DIR)/bin
SRC_DIR  = $(BASE_DIR)/src
OBJ_DIR  = $(BASE_DIR)/obj
INC_DIR  = $(BASE_DIR)/include

OBJ_EXT = o

ROOT_FLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT_LIBS  = $(shell $(ROOTSYS)/bin/root-config --libs)

FLAGS  	+= -O3 -Wall -fPIC
INCLUDE	+= -I$(INC_DIR)
FLAGS   += ${INCLUDE}
FLAGS   += ${ROOT_FLAGS}
LIBS    += ${ROOT_LIBS}

BOOST_DIR = /usr/local
INCLUDE += -I$(BOOST_DIR)/include
LIBS    += -L$(BOOST_DIR)/lib

USER_LIBS     += -L$(LIB_DIR) -lStools -lMonkey
USER_INCLUDES += -I../Stools/include/
USER_INCLUDES += -I../Monkey/include/
INCLUDE += $(USER_INCLUDES)
LIBS += $(USER_LIBS)

CXX = g++
LD  = g++
CXXFLAGS = -Wall -W -O3
LDFLAGS = -shared -Wall -W

FLAGS += $(USER_INCLUDES)

# Build a list of srcs and bins to build
SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(subst $(SRC_DIR), $(OBJ_DIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))
BINS=$(subst $(BIN_DIR), $(SRC_DIR),$(subst .cpp,,$(EXES)))


all: $(OBJS) lib

$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CXX) $(FLAGS) -c $< -o $@

$(LIB_DIR)/lib$(LIBNAME).so: $(OBJS)
	$(LD) $(LDFLAGS) -shared -o $(LIB_DIR)/lib$(LIBNAME).so $(OBJS) $(LIBS)

lib: $(LIB_DIR)/lib$(LIBNAME).so

clean:
	rm -f $(OBJS) $(LIB_DIR)/lib$(LIBNAME).so


