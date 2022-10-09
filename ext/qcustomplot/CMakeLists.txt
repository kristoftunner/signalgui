cmake_minimum_required(VERSION 3.16)

find_package(Qt5 COMPONENTS Gui Widgets Core PrintSupport REQUIRED)

add_library(QCustomPlot STATIC ${CMAKE_CURRENT_SOURCE_DIR}/qcustomplot.cpp)

target_include_directories(QCustomPlot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(QCustomPlot PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport)