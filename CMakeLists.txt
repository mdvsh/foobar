cmake_minimum_required(VERSION 3.27)
project(foobar)

set(CMAKE_CXX_FLAGS "-O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#include(FetchContent)
#set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
#FetchContent_Declare(ftxui
#        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
#        GIT_TAG v5.0.0
#)
#FetchContent_MakeAvailable(ftxui)

add_executable(foobar
        src/main.cpp
        src/Editor.cpp
        src/Editor.h
        src/Terminal.cpp
        src/Terminal.h
        src/Buffer.cpp
        src/Buffer.h
        src/GapBuffer.cpp
        src/GapBuffer.h
)

#target_link_libraries(foobar PRIVATE ftxui::screen ftxui::dom)

if(MSVC)
    target_compile_options(foobar PRIVATE /W4)
else()
    target_compile_options(foobar PRIVATE -Wall -Wextra -Wpedantic)
endif()