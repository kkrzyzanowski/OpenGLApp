cmake_minimum_required(VERSION 3.14)
project(StbImageReader LANGUAGES CXX)

file(GLOB_RECURSE STB_SRCS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

if(STB_SRCS)
    add_library(stb_image_reader SHARED ${STB_SRCS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${STB_SRCS})

    target_include_directories(stb_image_reader PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/OpenGLApp
    )

    target_compile_definitions(stb_image_reader
        PRIVATE STBIMAGEREADER_EXPORTS
        PUBLIC _UNICODE UNICODE
    )

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")
        target_precompile_headers(stb_image_reader PRIVATE pch.h)
    endif()

    target_compile_features(stb_image_reader PUBLIC cxx_std_20)

    if(MSVC)
        target_compile_options(stb_image_reader PRIVATE /W4 /permissive-)
    else()
        target_compile_options(stb_image_reader PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    # Kopiowanie DLL obok GUI.exe jest zdefiniowane w GUI/CMakeLists.txt
    # (musi tam być, bo Stb_image_reader jest dodawany w root PRZED GUI,
    # więc target GUI jeszcze by tu nie istniał).

else()
    add_library(stb_image_reader INTERFACE)
    target_include_directories(stb_image_reader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
    message(WARNING "No source files found for Stb_image_reader; created INTERFACE target 'stb_image_reader'.")
endif()