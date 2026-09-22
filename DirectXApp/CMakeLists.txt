cmake_minimum_required(VERSION 3.14)
project(DirectXApp LANGUAGES CXX)

file(GLOB_RECURSE DIRECTX_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)
list(FILTER DIRECTX_SOURCES EXCLUDE REGEX ".*(/build/|/external/|/third_party/).*")

add_executable(${PROJECT_NAME} ${DIRECTX_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${DIRECTX_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Defines zgodne z command line
target_compile_definitions(${PROJECT_NAME} PRIVATE
    _UNICODE
    UNICODE
)

# Windows / DirectX
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)

    # Podstawowe biblioteki DirectX (dopasuj do tego czego faktycznie używasz:
    # d3d11 dla DirectX 11, d3d12 dla DirectX 12, itd.)
    target_link_libraries(${PROJECT_NAME} PRIVATE d3d11 dxgi d3dcompiler)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()