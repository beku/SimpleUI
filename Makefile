FLTK_FLAGS := $(shell (fltk-config --cflags --ldflags))
GTK_FLAGS := $(shell (pkg-config --cflags --libs gtk+-3.0))
XML_FLAGS := $(shell (xml2-config --cflags --libs))
CFLAGS = -g -Wall -fPIC -I./
TARGETS = SimpleUiFltk SimpleUiQt SimpleUiGtk

HEADER = sXforms.h io/io.h misc/misc.h xml/sXml.h sCallbackData/sCallbackData.h
SOURCES_LIB = io/io.c misc/string_func.c xml/sParseXforms.c sCallbackData/sCallbackData.c sXforms.c
OBJECTS_LIB = $(SOURCES_LIB:.c=.o)
CORE_LIB = libSimpleUiCore.so

all:	$(TARGETS)

libSimpleUiCore.a:	$(OBJECTS_LIB) $(HEADER)
	ar cru libSimpleUiCore.a $(OBJECTS_LIB)

libSimpleUiCore.so:	$(OBJECTS_LIB) $(HEADER)
	gcc -shared -o libSimpleUiCore.so $(OBJECTS_LIB)

SimpleUiQt:
	(cd qt; qmake; make; cp -av sQt ../SimpleUiQt)

SimpleUiFltk:	$(CORE_LIB) fltk/sFltk.cxx fltk/sFltkWidgets.cxx fltk/sFltkCallbacks.cxx $(HEADER)
	$(CXX)  $(CFLAGS) -o 'SimpleUiFltk' fltk/sFltk.cxx fltk/sFltkWidgets.cxx fltk/sFltkCallbacks.cxx $(CORE_LIB) $(XML_FLAGS) $(FLTK_FLAGS)

SimpleUiGtk: 	$(CORE_LIB) gtk/sGtk.c gtk/sGtkRenderers/sGtkParseTree.c gtk/sGtkRenderers/sGtkRenderer_Helper.c gtk/sGtkCallbacks/sGtkCallbacks.c gtk/sGtkCallbacks/sGtkCallback_SetValues.c gtk/sGtkCallbacks/sGtkCallback_GetValues.c
	$(CC)  $(CFLAGS) -o 'SimpleUiGtk' gtk/sGtk.c gtk/sGtkRenderers/sGtkParseTree.c gtk/sGtkRenderers/sGtkRenderer_Helper.c gtk/sGtkCallbacks/sGtkCallbacks.c gtk/sGtkCallbacks/sGtkCallback_SetValues.c gtk/sGtkCallbacks/sGtkCallback_GetValues.c $(CORE_LIB) $(XML_FLAGS) $(GTK_FLAGS)

# Build commands and filename extensions...
.SUFFIXES:	.c

.SILENT:
.PHONY:	SimpleUiQt


.c.o:
	echo Compiling $< ...
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-(cd qt/; make distclean)
	-rm *.o $(TARGETS)
	-rm io/*.o
	-rm misc/*.o
	-rm sCallbackData/*.o
	-rm xml/*.o
	-rm libSimpleUiCore*
