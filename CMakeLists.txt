project(FileSync)
cmake_minimum_required(VERSION 2.6)

option("WANT_SERVER     "Build the server binary"           ON)
option("WANT_CLIENT     "Build the server binary"           ON)

if(APPLE)
  option(DEPLOY        "Mac OS X only! Adds required libs to bundle resources and create a dmg. Note: requires Qt to be built with 10.4u SDK" OFF)
endif(APPLE)

if(APPLE AND DEPLOY)
#FIXME: Does 10.7 imply it only works on lion?
  set(CMAKE_OSX_ARCHITECTURES "x86_64")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.7")
  set(CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.7.sdk/")
  add_definitions(-DMAC_10_7_SDK)
endif(APPLE AND DEPLOY)

set(QT_MIN_VERSION "4.7.0")
SET(QT_USE_QTCORE true)
SET(QT_USE_QTNETWORK true)
SET(QT_USE_QTSQL true)
SET(QT_USE_QTGUI true)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
#include(MacroLibrary)
include(FindQt4)
include(FindProtobuf)
include(${QT_USE_FILE})
include(UsePkgConfig)



if(PROTOBUF_FOUND)
ELSE (PROTOBUF_FOUND)
	MESSAGE(FATAL_ERROR "Could not find libprotobuf headers")
ENDIF (PROTOBUF_FOUND)
IF(QT4_FOUND)
ELSE (QT4_FOUND)
	MESSAGE(FATAL_ERROR "Could not find QT4")
ENDIF (QT4_FOUND)

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)

set(qtproject_client_SRCS client/main.cpp ) 
set(qtproject_client__MOC_SRCS client/clientconnection.cpp client/manager.cpp ) 
set(qtproject_client__MOC_HEADERS client/manager.h client/clientconnection.h)

set(qtproject_common_SRCS common/connection.cpp ) 
set(qtproject_common__MOC_SRCS common/connection.cpp ) 
set(qtproject_common__MOC_HEADERS common/connection.h )


QT4_WRAP_CPP(qtproject_MOC_SRCS ${qtproject_MOC_HEADERS} ${qtproject_common_MOC_HEADERS})

#SET(qtproject_UIS )
#QT4_WRAP_UI(qtproject_UIS_H ${qtproject_UIS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDE_DIR}  ${PROTOBUF_INCLUDE} )
add_executable(FileShare ${qtproject_client_SRCS} ${qtproject_client_MOC_SRCS} 
			   ${qtproject_common_SRCS} ${qtproject_common_MOC_SRCS}  ${qtproject_UIS_H} )
			
target_link_libraries(FileShare ${QT_LIBRARIES} ${PROTOBUF_LIBRARY} )

#INSTALL(FILES ${install_headers} DESTINATION include/fileshare)
#INSTALL(TARGETS protorpcpp LIBRARY DESTINATION lib)