cmake_minimum_required(VERSION 3.20)
project("main")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdeclspec")
# dobby
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/includes/dobby")
link_libraries("${CMAKE_CURRENT_SOURCE_DIR}/includes/dobby/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a")
# ByNameModding
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ByNameModding")
add_library(${PROJECT_NAME} SHARED main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC log)
