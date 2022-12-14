cmake_minimum_required(VERSION 3.16)

find_package(Qt5 COMPONENTS Widgets UiTools Charts REQUIRED)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::UiTools Qt5::Charts pthread kfr)
target_include_directories(${PROJECT_NAME} 
  PRIVATE 
  /usr/include/x86_64-linux-gnu/qt5/QtWidgets
  /usr/include/x86_64-linux-gnu/qt5/QtCharts
  /usr/include/x86_64-linux-gnu/qt5/QtCore
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(${PROJECT_NAME} PUBLIC -std=gnu++17 -lstdc++fs -ggdb)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOMOC ON)