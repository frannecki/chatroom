cmake_minimum_required(VERSION 3.5.0)
project(chatroom)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(Qt5  REQUIRED COMPONENTS  Widgets Core Gui Qml Quick)

if(Qt5_FOUND)
  file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.ui)
  file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
  file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)

  add_library(${PROJECT_NAME} SHARED
              ${QT_FORMS}
              src/common_.cpp src/thread_client.cpp src/thread_server.cpp
              src/mainwindow_client.cpp src/mainwindow_server.cpp src/tabpage.cpp
             )

  target_link_libraries(${PROJECT_NAME}
                        ${QT_LIBRARIES}
                        Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::Widgets
                       )

  add_executable(clientui src/main_client.cpp ${QT_RESOURCES} ${QT_MOC})
  target_link_libraries(clientui ${PROJECT_NAME})

  add_executable(serverui src/main_server.cpp ${QT_RESOURCES} ${QT_MOC})
  target_link_libraries(serverui ${PROJECT_NAME})
endif()