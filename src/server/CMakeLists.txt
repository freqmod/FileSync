
set(SOURCES 
                main.cpp
                serverconnection.cpp )
set(MOC_HDRS
               serverconnection.h )
set(HEADERS 
                 )


qt4_wrap_cpp(MOC ${MOC_HDRS})

include_directories(${CMAKE_SOURCE_DIR}/src/common ${CMAKE_BINARY_DIR}/src/common)

add_library(mod_server STATIC ${SOURCES} ${MOC} ${HEADERS})
add_dependencies(mod_server mod_common)

