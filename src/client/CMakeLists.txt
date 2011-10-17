SET(QT_USE_QTGUI true)

set(SOURCES 
               main.cpp
               clientconnection.cpp
               manager.cpp )
set(MOC
                manager.h
                clientconnection.h )
set(HEADERS 
                )


qt4_wrap_cpp(MOC ${MOC_HDRS})

include_directories(${CMAKE_SOURCE_DIR}/src/common ${CMAKE_BINARY_DIR}/src/common)

add_library(mod_client STATIC ${SOURCES} ${MOC} ${HEADERS})
add_dependencies(mod_client mod_common)

