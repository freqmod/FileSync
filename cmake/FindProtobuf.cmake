#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
# 

# Author: Frederik M.J. 
# Author(wrap command): Esben Mose Hansen <esben at ange.dk>, (C) Ange Optimization ApS 2008
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

#IF (WIN32)
# 	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
# 		$ENV{PROGRAMFILES}/GLEW/include
# 		${PROJECT_SOURCE_DIR}/src/nvgl/glew/include
# 		DOC "The directory where GL/glew.h resides")
# 	FIND_LIBRARY( GLEW_LIBRARY
# 		NAMES glew GLEW glew32 glew32s
# 		PATHS
# 		$ENV{PROGRAMFILES}/GLEW/lib
# 		${PROJECT_SOURCE_DIR}/src/nvgl/glew/bin
# 		${PROJECT_SOURCE_DIR}/src/nvgl/glew/lib
# 		DOC "The GLEW library")
FIND_PATH( PROTOBUF_INCLUDE google/protobuf/descriptor.h
	/usr/include
	/usr/local/include
	/sw/include
	/opt/local/include
	DOC "The directory where google/protobuf/descriptor.h resides")

FIND_LIBRARY( PROTOBUF_LIBRARY
	NAMES protobuf
	PATHS
	/usr/lib64
	/usr/lib
	/usr/local/lib64
	/usr/local/lib
	/sw/lib
	/opt/local/lib
	DOC "The protobuf library")

FIND_PROGRAM(PROTOBUF_PROTOC_EXECUTABLE 
	NAMES protoc
	PATHS
	/usr/bin64
	/usr/bin
	/usr/local/bin64
	/usr/local/bin
	/sw/bin
	/opt/local/bin)

IF (PROTOBUF_INCLUDE)
	SET( PROTOBUF_FOUND 1 CACHE STRING "Set to 1 if PROTOBUF is found, 0 otherwise")
ELSE (PROTOBUF_INCLUDE)
	SET( PROTOBUF_FOUND 0 CACHE STRING "Set to 1 if PROTOBUF is found, 0 otherwise")
ENDIF (PROTOBUF_INCLUDE)

MARK_AS_ADVANCED( PROTOBUF_FOUND )

IF (PROTOBUF_FOUND)
  # Define the WRAP_PROTO function
  FUNCTION(WRAP_PROTO VAR)
    IF (NOT ARGN)
      MESSAGE(SEND_ERROR "Error: WRAP PROTO called without any proto files")
      RETURN()
    ENDIF(NOT ARGN)

    SET(${VAR}_HEADERS)
    SET(${VAR})
    FOREACH(FIL ${ARGN})
      GET_FILENAME_COMPONENT(ABS_FIL ${FIL} ABSOLUTE)
      GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)
      LIST(APPEND ${VAR} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc")
      LIST(APPEND ${VAR}_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h")

      ADD_CUSTOM_COMMAND(
        OUTPUT ${${VAR}} ${${VAR}_HEADERS}
        COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS --cpp_out  ${CMAKE_CURRENT_BINARY_DIR} --proto_path ${CMAKE_CURRENT_SOURCE_DIR} ${ABS_FIL}
        DEPENDS ${ABS_FIL}
        COMMENT "Running protocol buffer compiler on ${FIL}"
        VERBATIM )
        
    ENDFOREACH(FIL)

    SET(${VAR} ${${VAR}} PARENT_SCOPE)

  ENDFUNCTION(WRAP_PROTO)
ENDIF(PROTOBUF_FOUND)