# name of the library
LIBNAME = Monkey

#Necessary to use shell built-in commands
SHELL = bash

# A list of directories
BASE_DIR = $(shell pwd)
LIB_DIR  = $(BASE_DIR)/lib
EXE_DIR  = $(BASE_DIR)/bin
SRC_DIR  = $(BASE_DIR)/src
OBJ_DIR  = $(BASE_DIR)/obj
INC_DIR  = $(BASE_DIR)/include

OBJ_EXT = o

FLAGS  		 = -O3 -Wall -W -fPIC
INCLUDE		+= -I$(INC_DIR)
FLAGS       += ${INCLUDE}
FLAGS       += ${ROOT_FLAGS}
#FLAGS       += -lRooFitCore -lRooFit -lRooStats -lFoam
LIBS         = ${ROOT_LIBS}

BOOST_DIR = /usr/local
INCLUDE += -I$(BOOST_DIR)/include
LIBS    += -L$(BOOST_DIR)/lib


ROOT_FLAGS  := $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT_LIBS   := $(shell $(ROOTSYS)/bin/root-config --libs)

SCPH_DIR=../
USER_LIBS += -L$(SCPH_DIR)/Stools/lib/ -lStools

#USER_INCLUDES += -I$(SCPH_DIR)/Easel/include/
USER_INCLUDES += -I$(SCPH_DIR)/Stools/include/
#USER_INCLUDES += -I$(SCPH_DIR)/Knives/include/

ROOT_LIBS += $(USER_LIBS)

CXX = g++
LD  = g++
CXXFLAGS = -Wall -W -O3
LDFLAGS  = -shared -Wall -W

#FLAGS += $(USER_LIBS)
FLAGS += $(USER_INCLUDES)

# Build a list of srcs and bins to build
SRCS = $(filter-out $(wildcard $(SRC_DIR)/_*), $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(subst $(SRC_DIR), $(OBJ_DIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))
BINS = $(subst $(BIN_DIR), $(SRC_DIR),$(subst .cpp,,$(EXES)))

all: $(OBJS) lib

$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CXX) $(FLAGS) -c $< -o $@

$(LIB_DIR)/lib$(LIBNAME).so: $(OBJS)
	$(LD) $(LDFLAGS) -shared -o $(LIB_DIR)/lib$(LIBNAME).so $(OBJS) $(ROOT_LIBS)
	cp -f $(LIB_DIR)/lib$(LIBNAME).so $(SCPH_DIR)/lib/lib$(LIBNAME).so

lib: $(LIB_DIR)/lib$(LIBNAME).so

clean:
	rm -f $(OBJS) $(LIB_DIR)/*.so

copy:
	cp -f $(LIB_DIR)/lib$(LIBNAME).so $(SCPH_DIR)/lib/.

info:
	@echo SRCS $(SRCS)
	@echo OBJS $(OBJS)

