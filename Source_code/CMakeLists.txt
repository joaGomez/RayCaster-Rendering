cmake_minimum_required(VERSION 3.0.0)
project(RayCaster-Rendering VERSION 0.1.0)

include(CTest)
enable_testing()

# Packages
find_package(raylib CONFIG REQUIRED)

# Main executable
add_executable(RayCaster-Rendering main.cpp Game.cpp Gameview.cpp Player.cpp Map.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS} ${MOSQUITTO_INCLUDE_DIRS})
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # From "Working with CMake" documentation:
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib m ${CMAKE_DL_LIBS} pthread GL rt X11)
endif()