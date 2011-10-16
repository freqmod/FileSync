
set(SOURCES client/main.cpp ) 
set(SOURCES client/clientconnection.cpp client/manager.cpp ) 
set(HEADERS client/manager.h client/clientconnection.h)

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