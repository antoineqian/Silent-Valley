cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -g ")


project(silentValley)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS  src/*.cpp)

add_library(silentValleyLib SHARED ${SRC_FILES})

# target_link_directories(silentValleyLib PUBLIC /usr/local/include/SFML/)

target_link_libraries(silentValleyLib
    /Library/Frameworks/SFML.framework
    /Library/Frameworks/sfml-system.framework/sfml-system
    /Library/Frameworks/sfml-window.framework/sfml-window
    /Library/Frameworks/sfml-graphics.framework/sfml-graphics
)


add_executable(silentValley src/main.cpp)
target_link_libraries(silentValley PRIVATE
    silentValleyLib
)

add_subdirectory(test)

