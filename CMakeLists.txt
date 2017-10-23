cmake_minimum_required(VERSION 3.8)
project(QTC_Generator)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5Widgets REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)

set(SOURCE_FILES main.cpp MainWindow.cpp MainWindow.hpp TestCase.cpp TestCase.hpp DraggableButton.cpp DraggableButton.hpp)
add_executable(QTC_Generator ${SOURCE_FILES})

target_link_libraries(QTC_Generator Qt5::Widgets)