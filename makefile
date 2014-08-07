FLTK_FLAGS := $(shell (fltk-config --cflags --ldflags))
GTK_FLAGS := $(shell (pkg-config --cflags --libs gtk+-3.0))
XML_FLAGS := $(shell (xml2-config --cflags --libs))

FLAGS = -Wall -g -Wno-unused-variable -Wno-unused-value -Wno-write-strings -Wno-unused-but-set-variable -Wno-return-type

TARGETS = sFltk sGtk sKde

FLTK_SOURCES =	\
	fltk/sFltk.cxx \
	fltk/sFltkWidgets.cxx \
	fltk/sFltkCallbacks.cxx
GTK_SOURCES = 	\
	gtk/sGtk.c \
	gtk/sGtkCallbacks/sGtkCallbacks.c \
	gtk/sGtkCallbacks/sGtkCallback_GetValues.c \
	gtk/sGtkCallbacks/sGtkCallback_SetValues.c \
        gtk/sGtkRenderers/sGtkParseTree.c \
        gtk/sGtkRenderers/sGtkRenderer_Helper.c
MISC_SOURCES =	\
	io/io.c \
	xml/sParseXforms.c \
	sXforms.c \
	sCallbackData/sCallbackData.c \
	misc/string_func.c

all:	$(TARGETS)

sFltk:
	g++ $(FLAGS) -o sFltk $(FLTK_SOURCES) $(MISC_SOURCES) $(XML_FLAGS) $(FLTK_FLAGS)

sGtk:
	gcc $(FLAGS) -o  sGtk $(GTK_SOURCES) $(MISC_SOURCES) $(XML_FLAGS) $(GTK_FLAGS) -export-dynamic

sKde:	Makefile
	-make -f Makefile

Makefile:
	qmake

clean:
	-rm $(TARGETS)
	-make -f Makefile clean
