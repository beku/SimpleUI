#cmake file for building SimpleUI
 
PROJECT(SimpleUi)
SET( PACKAGE_NAME simpleui)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# project version
SET( ${PROJECT_NAME}_MAJOR_VERSION 0)
SET( ${PROJECT_NAME}_MINOR_VERSION 9)
SET( ${PROJECT_NAME}_MICRO_VERSION 6)

SET( ${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_MICRO_VERSION} )

#additional cmake modules for loading libraries
SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE(LibXml2 REQUIRED)
INCLUDE_DIRECTORIES( ${LIBXML2_INCLUDE_DIR} )
LINK_DIRECTORIES( ${LIBXML2_LIBRARY_DIRS} )
IF(LIBXML2_FOUND)
  SET( HAVE_LIBXML2 1 )
  SET( LIBXML2_LIBRARIES ${LIBXML2_LIBRARIES})
ENDIF(LIBXML2_FOUND)

# i18n
FIND_PACKAGE( GetText )
MESSAGE( "GetText: ${GETTEXT_FOUND}" )
IF( GETTEXT_FOUND )
  SET( USE_GETTEXT TRUE )
ENDIF()

IF( GETTEXT_FOUND )
  SET(_potFile ${CMAKE_SOURCE_DIR}/po/${PACKAGE_NAME}.pot)
  #SET( _xgettext_option_list --language=C --keyword=_ --keyword=N_ --keyword=C_:1c,2 --keyword=NC_:1c,2 -s --package-name=${PROJECT_NAME} --package-version=${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION} )
  SET( _xgettext_option_list --add-comments --keyword=gettext --flag=gettext:1:pass-c-format --keyword=_ --flag=_:1:pass-c-format --keyword=N_ --flag=N_:1:pass-c-format  --copyright-holder='Kai-Uwe Behrmann'  --msgid-bugs-address='ku.b@gmx.de' --from-code=utf-8 --package-name=${PROJECT_NAME} --package-version=${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION} )
  SET( XGETTEXT_CMD xgettext )
  FILE( GLOB SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.c io/*.c misc/*.c sCallbackData/*.c qt/*.cpp xml/*.c
      )

  ADD_CUSTOM_COMMAND(OUTPUT ${_potFile}
    COMMAND ${XGETTEXT_CMD} ${_xgettext_option_list} -o ${_potFile} ${SRC_FILES}
    DEPENDS ${SRC_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Extract translatable messages to ${_potFile}"
  )

  SET( LINGUAS po/cs.po po/de.po po/eo.po po/eu.po po/fr.po )
  # compile translations always to have them ready for installation
  GETTEXT_CREATE_TRANSLATIONS( ${_potFile} ALL ${LINGUAS} )
ENDIF()


SET( ${CMAKE_BUILD_TYPE} Debug)

#now add all directories
ADD_SUBDIRECTORY( qt )

CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PACKAGE_NAME}Uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PACKAGE_NAME}Uninstall.cmake"
    IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET( uninstall
	"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PACKAGE_NAME}Uninstall.cmake")

ADD_CUSTOM_TARGET( dist
                COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/ && git archive --prefix=${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/ --format=tar HEAD > ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar
                COMMAND echo "git sha1:  " | tr -d "\\n" >> ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/ && git rev-parse HEAD >> ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND rm -rf ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION} && tar xf ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar
                COMMAND tar cf - ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION} | bzip2 > ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2
                COMMAND echo  "size:      " | tr -d "\\n" >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND du -b ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2 | sed s/[[:space:]][[:print:]]*// >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND echo  "md5sum:    " | tr -d "\\n" >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/ && md5sum ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2 >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND echo  "sha1sum:   " | tr -d "\\n" >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND sha1sum ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2 >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND echo  "sha256sum: " | tr -d "\\n" >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMAND sha256sum ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2 >> ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2.hashsum
                COMMENT Make a ${PACKAGE_NAME} source package by using git
                VERBATIM
                WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                )
EXECUTE_PROCESS(COMMAND rpmbuild --showrc
                COMMAND awk '/^build arch/ {print $$4}'
                OUTPUT_VARIABLE RPMARCH
                ERROR_VARIABLE RPMBUILD_ERROR
               )
ADD_CUSTOM_TARGET( rpm
		COMMAND test -d ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/ && rm -rf ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/
		COMMAND tar xjf ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2
                COMMAND mkdir -p rpmdir/BUILD rpmdir/SPECS rpmdir/SOURCES rpmdir/SRPMS rpmdir/RPMS/${RPMARCH}
                COMMAND cp -f ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2 rpmdir/SOURCES
                COMMAND rpmbuild --clean -ba extras/${PACKAGE_NAME}.spec --define "_topdir ${CMAKE_CURRENT_BINARY_DIR}/rpmdir"
                DEPENDS dist
		COMMENT Make a ${PACKAGE_NAME} RPM package
		VERBATIM
		)

ADD_CUSTOM_TARGET( debsrc
		COMMAND test -d ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/ && rm -rf ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/
		COMMAND tar xjf ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2
                COMMAND mv ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}.tar.bz2 ${PACKAGE_NAME}_${${PROJECT_NAME}_VERSION}.orig.tar.bz2
                COMMAND cp -R ${CMAKE_SOURCE_DIR}/extras/debian ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/
                COMMAND dpkg-source -b ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/
                DEPENDS dist
		COMMENT Make a ${PROJECT_NAME} DEB source package
		VERBATIM
		)
ADD_CUSTOM_TARGET( debian
		COMMAND cd ${PACKAGE_NAME}-${${PROJECT_NAME}_VERSION}/ && debuild
                DEPENDS debsrc
		COMMENT Make a ${PROJECT_NAME} DEB package
		VERBATIM
		)

 
# --- extra modules ---

ADD_LIBRARY( ${PROJECT_NAME}Core
             SHARED
             sXforms.c
             io/io.c
             misc/string_func.c
             sCallbackData/sCallbackData.c
             xml/sParseXforms.c
              )
TARGET_LINK_LIBRARIES ( ${PROJECT_NAME}Core ${LIBXML2_LIBRARIES} ${EXTRA_LIBS} )
INSTALL (TARGETS ${PROJECT_NAME}Core DESTINATION lib${LIB_SUFFIX})
