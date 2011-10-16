set(SOURCES 
                connection.cpp
                prototools.cpp )
set(MOC_HDRS
                connection.h )
set(HEADERS
                prototools.h )
set(PROTOS
                filesync.proto )

qt4_wrap_cpp(MOC ${MOC_HDRS})
wrap_proto(PROTO_SOURCES ${PROTOS})

include_directories(${CMAKE_SOURCE_DIR}/src/common ${CMAKE_CURRENT_BINARY_DIR})

add_library(mod_common STATIC ${SOURCES} ${PROTO_SOURCES} ${MOC} ${HEADERS} ${PROTO_SOURCES_HEADERS})
#add_dependencies(mod_client mod_common)

