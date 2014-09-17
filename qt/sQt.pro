 CONFIG      += uitools qt warn_on debug
 CONFIG      += link_pkgconfig
 PKGCONFIG   += libxml-2.0

DEPENDPATH += . sQtCallbacks sQtRenderers
INCLUDEPATH += . sQtCallbacks sQtRenderers
LIBS    += -L../ -lSimpleUiCore

HEADERS += sQt.h \
           sQtCallbacks/sQt_Cb.h \
           sQtRenderers/sQtRenderer.h
SOURCES += main.cpp \
           sQt.cpp \
           sQtCallbacks/sQt_Cb.cpp \
           sQtRenderers/sQtParseTree.cpp \
           sQtRenderers/sQtRenderer_Helper.cpp

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/designer/calculatorbuilder
 sources.files = $$SOURCES $$HEADERS $$RESOURCES *.ui *.pro
 sources.path = $$[QT_INSTALL_EXAMPLES]/designer/calculatorbuilder
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
