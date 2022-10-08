cmake_minimum_required(VERSION 3.16)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME} app.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)