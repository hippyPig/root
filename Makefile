#Necessary to use shell built-in commands
SHELL=bash

SUBDIRS += Stools
SUBDIRS += Monkey
SUBDIRS += Knives
SUBDIRS += Dendrology


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


clean:
	rm -f lib/*.so
	$(MAKE) -C Stools/ clean
	$(MAKE) -C Monkey/ clean
	$(MAKE) -C Knives/ clean
	$(MAKE) -C Dendrology/ clean

info:
	@echo $(LIBS)

