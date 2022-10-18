cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-Wall -g")

project(silentValley)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS  src/*.cpp)
add_executable(silentValley ${SRC_FILES})

add_library(silentValleyLib SHARED ${SRC_FILES})
target_link_libraries(silentValley PRIVATE
    silentValleyLib
)


