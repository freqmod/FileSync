project(FileSync)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(QuasselMacros)
option(WANT_SERVER     "Build the client binary"           ON)
option(WANT_CLIENT     "Build the server binary"           ON)

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

#include(MacroLibrary)
include(FindQt4)
include(FindProtobuf)
include(${QT_USE_FILE})
#include(UsePkgConfig)

if(PROTOBUF_FOUND)
ELSE (PROTOBUF_FOUND)
	MESSAGE(FATAL_ERROR "Could not find libprotobuf headers")
ENDIF (PROTOBUF_FOUND)
IF(QT4_FOUND)
ELSE (QT4_FOUND)
	MESSAGE(FATAL_ERROR "Could not find QT4")
ENDIF (QT4_FOUND)

# Now set up install locations; those are set by KDE if integration is enabled
if(WIN32)
  set(BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX} CACHE FILEPATH "Install path for binaries")
  set(DATA_INSTALL_DIR $ENV{APPDATA}/filesync/share/apps CACHE FILEPATH "Install path for data files")
  set(ICON_INSTALL_DIR $ENV{APPDATA}/filesync/share/icons CACHE FILEPATH "Global icon install path")
  set(XDG_APPS_INSTALL_DIR $ENV{APPDATA}/filesync/share/applications CACHE FILEPATH "Install path for .desktop files")
else(WIN32)
  set(BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin CACHE FILEPATH "Install path for binaries")
  set(DATA_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/apps CACHE FILEPATH "Install path for data files")
  set(ICON_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/icons CACHE FILEPATH "Global icon install path")
  set(XDG_APPS_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/applications CACHE FILEPATH "Install path for .desktop files")
endif(WIN32)


add_subdirectory(src)
