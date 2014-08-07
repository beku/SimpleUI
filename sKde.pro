 CONFIG      += uitools debug
 CONFIG      += link_pkgconfig
 PKGCONFIG   += libxml-2.0

 HEADERS     = kde/sKDE.h \
               kde/sKdeCallbacks/sKde_Cb.h \
 RESOURCES   = kde/sKde.qrc
 SOURCES     = kde/sKde.cpp \
               kde/main.cpp \
               kde/sKdeCallbacks/sKde_Cb.cpp \
               kde/sKdeRenderers/sKdeParseTree.cpp \
               kde/sKdeRenderers/sKdeRenderer_Helper.cpp \
               sXforms.c \
               io/io.c \
               misc/string_func.c \
	       sCallbackData/sCallbackData.c \
               xml/sParseXforms.c

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/designer/calculatorbuilder
 sources.files = $$SOURCES $$HEADERS $$RESOURCES *.ui *.pro
 sources.path = $$[QT_INSTALL_EXAMPLES]/designer/calculatorbuilder
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
