cmake_minimum_required(VERSION 3.3)

project(SpeedReader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(SOURCE_FILES main.cpp mainwindow.cpp textdisplaywidget.cpp AppController.cpp AppController.hpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)



set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/shein/Qt/5.12.2/clang_64/lib/cmake")
find_package(Qt5Widgets REQUIRED)


add_executable(SpeedReader ${SOURCE_FILES})
target_link_libraries(SpeedReader Qt5::Widgets)