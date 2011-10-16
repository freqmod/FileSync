project(FileShare)

cmake_minimum_required(VERSION 2.6)
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

set(qtproject_SRCS main.cpp ) 
set(qtproject_MOC_SRCS clientconnection.cpp manager.cpp ) 
set(qtproject_MOC_HEADERS manager.h clientconnection.h)

QT4_WRAP_CPP(qtproject_MOC_SRCS ${qtproject_MOC_HEADERS})

#SET(qtproject_UIS )
#QT4_WRAP_UI(qtproject_UIS_H ${qtproject_UIS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDE_DIR}  ${PROTOBUF_INCLUDE} )
add_executable(FileShare ${qtproject_SRCS} ${qtproject_MOC_SRCS}  ${qtproject_UIS_H} )
target_link_libraries(FileShare ${QT_LIBRARIES} ${PROTOBUF_LIBRARY} )

#INSTALL(FILES ${install_headers} DESTINATION include/fileshare)
#INSTALL(TARGETS protorpcpp LIBRARY DESTINATION lib)