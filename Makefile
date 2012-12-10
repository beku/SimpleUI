FLTK_FLAGS := $(shell (fltk-config --cflags --libs))
GTK_FLAGS := $(shell (pkg-config --cflags --libs gtk+-3.0))
XML_FLAGS := $(shell (xml2-config --cflags --libs))
CFLAGS = -g -Wall -I./
TARGETS = SimpleUIFltk SimpleUIQt SimpleUIGtk

HEADER = sXforms.h io/io.h misc/misc.h xml/sXml.h sCallbackData/sCallbackData.h

all:	$(TARGETS)

libSimpleUICore.a:	io/io.o misc/string_func.o xml/sParseXforms.o sCallbackData/sCallbackData.o sXforms.o $(HEADER)
	ar cru libSimpleUICore.a io/io.o misc/string_func.o xml/sParseXforms.o sCallbackData/sCallbackData.o sXforms.o

SimpleUIQt:
	(cd Qt; qmake; make; cp Qt ../SimpleUIQt)

SimpleUIFltk: libSimpleUICore.a FLTK/sFltk.cxx FLTK/sFltkWidgets.cxx FLTK/sFltkCallbacks.cxx $(HEADER)
	$(CXX)  $(CFLAGS) -o 'SimpleUIFltk' FLTK/sFltk.cxx FLTK/sFltkWidgets.cxx FLTK/sFltkCallbacks.cxx libSimpleUICore.a $(XML_FLAGS) $(FLTK_FLAGS_) -lfltk

SimpleUIGtk: libSimpleUICore.a Gtk/sGtk.c Gtk/sGtkRenderers/sGtkParseTree.c Gtk/sGtkRenderers/sGtkRenderer_Helper.c Gtk/sGtkCallbacks/sGtkCallbacks.c ./Gtk/sGtkCallbacks/sGtkCallback_SetValues.c ./Gtk/sGtkCallbacks/sGtkCallback_GetValues.c
	$(CC)  $(CFLAGS) -o 'SimpleUIGtk' Gtk/sGtk.c Gtk/sGtkRenderers/sGtkParseTree.c Gtk/sGtkRenderers/sGtkRenderer_Helper.c Gtk/sGtkCallbacks/sGtkCallbacks.c ./Gtk/sGtkCallbacks/sGtkCallback_SetValues.c ./Gtk/sGtkCallbacks/sGtkCallback_GetValues.c libSimpleUICore.a $(XML_FLAGS) $(GTK_FLAGS)

# Build commands and filename extensions...
.SUFFIXES:	.c

.c.o:
	echo Compiling $< ...
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-(cd Qt/; make distclean)
	-rm *.o $(TARGETS)
	-rm io/*.o
	-rm misc/*.o
	-rm sCallbackData/*.o
	-rm xml/*.o
	-rm libSimpleUICore.a
