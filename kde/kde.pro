######################################################################
# Automatically generated by qmake (2.01a) Tue Aug 14 10:10:01 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . sKdeCallbacks sKdeRenderers
INCLUDEPATH += . sKdeCallbacks sKdeRenderers

LIBS += -lxml2

# Input
CONFIG += uitools
HEADERS += sKDE.h \
           sKdeCallbacks/sKde_Cb.h \
           sKdeRenderers/sKdeRenderer.h \
           ../sCallbackData/sCallbackData.h \
           ../misc/misc.h \
           ../simpleUI.h \
           ../sXforms.h \
           ../xml/sXml.h \
 	   ../io/io.h
SOURCES += main.cpp \
           sKDE.cpp \
           sKdeCallbacks/sKde_Cb.cpp \
           sKdeRenderers/sKdeParseTree.cpp \
           sKdeRenderers/sKdeRenderer_Helper.cpp \
           ../sXforms.c \
           ../sCallbackData/sCallbackData.c \
           ../misc/string_func.c \
           ../xml/sParseXforms.c \
	   ../io/io.c

