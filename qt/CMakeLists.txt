# SimpleUI Qt Renderer
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtUiTools)
IF(QT_FOUND)
  SET( HAVE_QT 1 )
  INCLUDE_DIRECTORIES( ${QT_INCLUDE_DIRS} )
  LINK_DIRECTORIES( ${QT_LIBRARY_DIRS} )
ENDIF(QT_FOUND)

IF( QT_FOUND AND UNIX AND NOT APPLE )
  INCLUDE( ${QT_USE_FILE} )

  SET( qt_SRCS
           main.cpp
           sQt.cpp
           sQtCallbacks/sQt_Cb.cpp
           sQtRenderers/sQtParseTree.cpp
           sQtRenderers/sQtRenderer_Helper.cpp
     )
  SET( qt_MOC_HEADERS
           sQt.h
           sQtCallbacks/sQt_Cb.h
           sQtRenderers/sQtRenderer.h
     )
  QT4_WRAP_CPP( qt_SRCS ${qt_MOC_HEADERS} )

  ADD_EXECUTABLE( ${PROJECT_NAME}Qt ${qt_SRCS} ${qt_RCC_SRCS} )
  TARGET_LINK_LIBRARIES ( ${PROJECT_NAME}Qt ${PROJECT_NAME}Core ${XML2_LIBRARIES}
                 ${QT_LIBRARIES} )
  INSTALL( TARGETS ${PROJECT_NAME}Qt DESTINATION bin )
#  INSTALL( FILES simpleuiqt.desktop DESTINATION share/applications )
#  INSTALL( FILES simpleuiqt.svg DESTINATION share/pixmaps )
ENDIF()

