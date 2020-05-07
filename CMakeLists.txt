cmake_minimum_required(VERSION 3.5.0)
project(chatroom)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(AUTOGEN_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/autogen)
set(CMAKE_SKIP_BUILD_RPATH FALSE)

## in order to link libraries with relative path
## executables must be called from cmake souurce dir
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "./lib")
## or use set_target_properties alternatively for each target

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(BUILD_SERVER OFF)
option(BUILD_CLIENT ON)
option(USE_REDIS_CACHE ON)  ## use redis to cache message for offline users
if(USE_REDIS_CACHE)
  add_definitions(-DMSGCACHE)
endif()

find_package(Qt5  REQUIRED COMPONENTS  Widgets Core Gui Qml Quick)
find_package(Threads)
find_package(Boost COMPONENTS thread serialization REQUIRED)

if(Qt5_FOUND)

  file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)

  add_library(${PROJECT_NAME} SHARED
              src/utils.cpp
              ${QT_RESOURCES}
             )

  target_link_libraries(${PROJECT_NAME}
                        ${QT_LIBRARIES}
                        ${Boost_LIBRARIES}
                        Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::Widgets
                       )

  if(BUILD_SERVER)
    file(GLOB QT_FORMS_SERVER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/server/*.ui)
    file(GLOB_RECURSE QT_MOC_SERVER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/server/*.h)
    file(GLOB CPPS_SERVER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/server/*.cpp)
    add_library(${PROJECT_NAME}_server_form STATIC
                ${QT_FORMS_SERVER}  
                # Placing ${CPPS_SERVER} or ${QT_MOC_SERVER} here leads to failed autogen
               )
    add_library(${PROJECT_NAME}_server SHARED
                ${CPPS_SERVER}
                ${QT_MOC_SERVER}
               )
    target_link_libraries(${PROJECT_NAME}_server  
                          mysqlclient  
                          ${PROJECT_NAME}  
                          ${PROJECT_NAME}_server_form
                         )
    if(USE_REDIS_CACHE)
      target_link_libraries(${PROJECT_NAME}_server hiredis)
    endif()
    add_executable(serverui  src/main_server.cpp)
    target_link_libraries(serverui  ${PROJECT_NAME}_server)
  endif()

  if(BUILD_CLIENT)
    file(GLOB QT_FORMS_CLIENT RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/client/*.ui)
    file(GLOB_RECURSE QT_MOC_CLIENT RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/client/*.h)
    file(GLOB CPPS_CLIENT RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/client/*.cpp)
    add_library(${PROJECT_NAME}_client_form STATIC
                ${QT_FORMS_CLIENT}  
                # Placing ${CPPS_CLIENT} or ${QT_MOC_CLIENT} here leads to failed autogen
               )
    add_library(${PROJECT_NAME}_client SHARED
                ${CPPS_CLIENT}
		            ${QT_MOC_CLIENT}
               )
    target_link_libraries(${PROJECT_NAME}_client  ${PROJECT_NAME}  ${PROJECT_NAME}_client_form)
    add_executable(clientui  src/main_client.cpp)
    target_link_libraries(clientui  ${PROJECT_NAME}_client)
  endif()

endif()