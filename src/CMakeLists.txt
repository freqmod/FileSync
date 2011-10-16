# Builds the three main targets

add_subdirectory(common)
include_directories(BEFORE common)
if(WANT_SERVER)
  add_subdirectory(server)
  include_directories(BEFORE server)
endif(WANT_SERVER)
if(WANT_CLIENT)
  add_subdirectory(client)
  include_directories(BEFORE client)

#  if(STATIC)
#    link_directories(${QT_PLUGINS_DIR}/imageformats)
#    set(CLIENT_LIBS qjpeg qgif)
#  endif(STATIC)

endif(WANT_CLIENT)

#include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}) # for version.gen

# Add resources. Can't be done in other subdirs apparently.
# Note that these variables need to contain paths relative to src/ (this dir)
qt4_add_resources(CLIENT_DEPS ${CLIENT_RCS})
qt4_add_resources(SERVER_DEPS ${SERVER_RCS})
qt4_add_resources(COMMON_DEPS ${COMMON_RCS})

if(WANT_SERVER)
  setup_qt4_variables(CORE NETWORK SQL)
  add_executable(fsserver server/main.cpp ${COMMON_DEPS} ${CORE_DEPS})
  add_dependencies(fsserver i18n)
  set_target_properties(fsserver PROPERTIES
                                    COMPILE_FLAGS "-DQT_CORE_LIB -DQT_NETWORK_LIB -DQT_SQL_LIB -DBUILD_SERVER"
                                    OUTPUT_NAME ../fsserver)
  target_link_libraries(fsserver mod_server mod_common
                                    ${QT_LIBRARIES} ${PROTOBUF_LIBRARY} )
  install(TARGETS fsserver RUNTIME DESTINATION ${BIN_INSTALL_DIR})
endif(WANT_SERVER)

if(WANT_CLIENT)
  setup_qt4_variables(GUI NETWORK SQL)
  add_executable(fsclient WIN32 server/main.cpp ${COMMON_DEPS} ${CLIENT_DEPS})
  add_dependencies(fsclient i18n)
  set_target_properties(fsclient PROPERTIES
                                      COMPILE_FLAGS "-DQT_GUI_LIB -DQT_NETWORK_LIB -DBUILD_QTUI"
                                      OUTPUT_NAME ../fsclient)
  target_link_libraries(fsclient mod_client mod_common ${CLIENT_LIBS}
                                      ${QT_LIBRARIES} ${PROTOBUF_LIBRARY} )
  install(TARGETS fsclient RUNTIME DESTINATION ${BIN_INSTALL_DIR})
endif(WANT_CLIENT)


# Build bundles for MacOSX
if(APPLE)
  add_custom_command(TARGET fsclient POST_BUILD
                     COMMAND ${CMAKE_SOURCE_DIR}/scripts/build/macosx_makebundle.py
                             ${CMAKE_SOURCE_DIR} "FileSync Client" ../fsclient)
  if(DEPLOY)
    add_custom_command(TARGET fsclient POST_BUILD
                       COMMAND ${CMAKE_SOURCE_DIR}/scripts/build/macosx_makePackage.sh Client ..)
    add_custom_command(TARGET fsserver POST_BUILD
                       COMMAND ${CMAKE_SOURCE_DIR}/scripts/build/macosx_makePackage.sh Server ..)
  endif(DEPLOY)
endif(APPLE)

