cmake_minimum_required(VERSION 3.14)
project(OpenGLApp LANGUAGES CXX)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)
list(FILTER APP_SOURCES EXCLUDE REGEX ".*(/build/|/external/|/third_party/).*")

add_library(${PROJECT_NAME} STATIC ${APP_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# OpenGL
find_package(OpenGL REQUIRED)
if(TARGET OpenGL::GL)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES})
endif()

# GLM (header-only)
if(TARGET glm)
    target_include_directories(${PROJECT_NAME} PUBLIC ${glm_SOURCE_DIR})
endif()

# GLFW
if(TARGET glfw)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
elseif(TARGET glfw3)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)
endif()

# GLEW
if(TARGET GLEW::GLEW)
    target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)
elseif(TARGET glew_s)
    target_link_libraries(${PROJECT_NAME} PUBLIC glew_s)
elseif(TARGET libglew_static)
    target_link_libraries(${PROJECT_NAME} PUBLIC libglew_static)
elseif(TARGET glew)
    target_link_libraries(${PROJECT_NAME} PUBLIC glew)
endif()

# Assimp
if(TARGET assimp)
    target_link_libraries(${PROJECT_NAME} PUBLIC assimp)
endif()

if(TARGET imgui)
    target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
endif()

if(TARGET stb_image_reader)
	target_link_libraries(${PROJECT_NAME} PUBLIC stb_image_reader)
endif()
# Jawne dodanie include dirs — stare CMakeLists GLEW/Assimp nie zawsze
# poprawnie eksportują je jako PUBLIC przez target_link_libraries
if(DEFINED glew_SOURCE_DIR)
    target_include_directories(${PROJECT_NAME} PUBLIC ${glew_SOURCE_DIR}/include)
endif()
if(DEFINED assimp_SOURCE_DIR)
    target_include_directories(${PROJECT_NAME} PUBLIC 
        ${assimp_SOURCE_DIR}/include
        ${assimp_BINARY_DIR}/include   # tu ląduje wygenerowany config.h
    )
endif()

# stb_image_reader
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Stb_image_reader
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    GLEW_STATIC
    _USE_MATH_DEFINES
)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

