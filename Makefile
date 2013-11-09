#Necessary to use shell built-in commands
SHELL=bash

SUBDIRS += Stools
SUBDIRS += Monkey
SUBDIRS += Knives
SUBDIRS += Easel
SUBDIRS += Dendrology

#LIBS = $(wildcard $(SUBDIRS)/lib/lib*.so)
#LIBS = $(addsuffix .so, $(SUBDIRS))
#LIBS = $(wildcard $(SUBDIRS)/lib/lib*)


all:  $(SUBDIRS)

.PHONY: $(SUBDIRS) $(LIBS)


$(SUBDIRS):
	$(MAKE) -C $@
	cp -f $@/lib/*.so lib/.


copy:
	cp -f Stools/lib/*.so lib/.
	cp -f Monkey/lib/*.so lib/.
	cp -f Knives/lib/*.so lib/.
	cp -f Dendrology/lib/*.so lib/.
	cp -f Easel/lib/*.so lib/.


clean:
	rm -f lib/*.so
	$(MAKE) -C Stools/ clean
	$(MAKE) -C Monkey/ clean
	$(MAKE) -C Knives/ clean
	$(MAKE) -C Dendrology/ clean
	$(MAKE) -C Easel/ clean

info:
	@echo $(LIBS)

