cmake_minimum_required(VERSION 3.0.0)

project(wxGLApp VERSION 0.1.0)

# Download and unpack library at configure time
configure_file(CMakeLists.txt.in OpenGLApp-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/OpenGLApp-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/OpenGLApp-download")

option(BUILD_LIBS_ONLY " " ON)
add_subdirectory("${CMAKE_BINARY_DIR}/OpenGLApp-src"
                 "${CMAKE_BINARY_DIR}/OpenGLApp-build")


set(MSYS true)
find_package(wxWidgets REQUIRED net core base gl ribbon adv aui)
include(${wxWidgets_USE_FILE})

add_executable(wxGLApp src/MainApp.cpp src/GLPanel.cpp)

set_property(TARGET wxGLApp PROPERTY CXX_STANDARD 17)

target_compile_options(wxGLApp PUBLIC -Wall -Wextra -Wundef -pedantic)

target_compile_definitions(wxGLApp PUBLIC __GNUWIN32__ ${wxWidgets_DEFINITIONS})

target_link_libraries(wxGLApp PUBLIC ${wxWidgets_LIBRARIES} te-graphic)

target_include_directories(wxGLApp PUBLIC include ${wxWidgets_INCLUDE_DIRS})

target_precompile_headers(wxGLApp PUBLIC include/pch.hpp)
