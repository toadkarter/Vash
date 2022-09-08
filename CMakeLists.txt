cmake_minimum_required(VERSION 3.10)
project(FilmAnalysis)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(frame src/Frame.cpp)

add_executable(main src/Main.cpp src/Frame.cpp include/Frame.h src/Video.cpp include/Video.h src/Mosaic.cpp include/Mosaic.h)

target_link_libraries(main frame ${OpenCV_LIBS})