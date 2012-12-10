FLTK_FLAGS := $(shell (fltk-config --cflags --libs))
GTK_FLAGS := $(shell (pkg-config --cflags --libs gtk+-3.0))
XML_FLAGS := $(shell (xml2-config --cflags --libs))
CFLAGS = -g -Wall -I./
TARGETS = SimpleUIFltk SimpleUIQt SimpleUIGtk

all:	$(TARGETS)

libSimpleUICore.a:	io/io.o misc/string_func.o xml/sParseXforms.o sCallbackData/sCallbackData.o sXforms.o
	ar cru libSimpleUICore.a io/io.o misc/string_func.o xml/sParseXforms.o sCallbackData/sCallbackData.o sXforms.o

SimpleUIQt:
	(cd kde; qmake; make; cp kde ../SimpleUIQt)

SimpleUIFltk: libSimpleUICore.a
	$(CXX)  $(CFLAGS) -o 'SimpleUIFltk' fltk/sFltk.cxx fltk/sFltkWidgets.cxx fltk/sFltkCallbacks.cxx io/io.o libSimpleUICore.a $(XML_FLAGS) $(FLTK_FLAGS_) -lfltk

SimpleUIGtk: libSimpleUICore.a
	$(CC)  $(CFLAGS) -o 'SimpleUIGtk' gtk/sGtk.c gtk/sGtkRenderers/sGtkParseTree.c gtk/sGtkRenderers/sGtkRenderer_Helper.c gtk/sGtkCallbacks/sGtkCallbacks.c ./gtk/sGtkCallbacks/sGtkCallback_SetValues.c ./gtk/sGtkCallbacks/sGtkCallback_GetValues.c libSimpleUICore.a $(XML_FLAGS) $(GTK_FLAGS)

# Build commands and filename extensions...
.SUFFIXES:	.c .cxx

.c.o:
	echo Compiling $< ...
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-(cd kde/; make distclean)
	-rm *.o $(TARGETS)
	-rm io/*.o
	-rm misc/*.o
	-rm sCallbackData/*.o
	-rm xml/*.o
	-rm libSimpleUICore.a
