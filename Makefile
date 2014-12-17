LIBNAME = Dendrology

# Necessary to use shell built-in commands
SHELL = bash

CXX = g++

# A list of directories
BASE_DIR = $(shell pwd)
LIB_DIR  = $(BASE_DIR)/lib
SRC_DIR  = $(BASE_DIR)/src
OBJ_DIR  = $(BASE_DIR)/obj
INC_DIR  = $(BASE_DIR)/include

OBJ_EXT = o

FLAGS  		 = -O3 -Wall -W -fPIC
LDFLAGS    = $(FLAGS) -shared

BOOST_DIR = /usr/local
BOOST_INC = -I$(BOOST_DIR)/include
BOOST_LIB = -L$(BOOST_DIR)/lib

ROOT_FLAGS   = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT_LIBS    = $(shell $(ROOTSYS)/bin/root-config --libs) -lTreePlayer -lXMLIO -lMLP -lRIO
ROOFIT_LIBS  = ${ROOT_LIBS} -lRooFitCore -lRooFit -lRooStats -lFoam

INCLUDE = -I$(INC_DIR) $(BOOST_INC)
LIBS    = $(BOOST_LIB) $(ROOFIT_LIBS)
FLAGS   += $(ROOT_FLAGS)

# Build a list of srcs and bins to build
SRCS = $(filter-out $(wildcard $(SRC_DIR)/_*), $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(subst $(SRC_DIR), $(OBJ_DIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))
BINS = $(subst $(BIN_DIR), $(SRC_DIR),$(subst .cpp,,$(EXES)))

all: $(OBJS) lib

$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CXX) $(FLAGS) $(INCLUDE) -c $< -o $@

$(LIB_DIR)/lib$(LIBNAME).so: $(OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(OBJS) -o $(LIB_DIR)/lib$(LIBNAME).so

lib: $(LIB_DIR)/lib$(LIBNAME).so

.PHONY: clean info

clean:
	rm -f $(OBJS) $(LIB_DIR)/lib$(LIBNAME).so

info:
	@echo SRCS $(SRCS)
	@echo OBJS $(OBJS)

