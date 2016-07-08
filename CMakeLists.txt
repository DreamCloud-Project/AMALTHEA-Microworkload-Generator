project (cmdline-microworkload-generator)

cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SOURCES FOLLOW_SYMLINKS "src/*.cpp" "src/*.cxx")
file(GLOB_RECURSE HEADERS FOLLOW_SYMLINKS "src/*.h" "src/*.hxx")

set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND simu_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${INCLUDE_DIRS})
include_directories($ENV{XERCES_HOME}/include)
link_directories($ENV{XERCES_HOME}/lib)
link_libraries(xerces-c)
add_executable (cmdline-microworkload-generator ${SOURCES})