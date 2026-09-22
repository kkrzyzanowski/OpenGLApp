cmake_minimum_required(VERSION 3.14)
project(GUI LANGUAGES CXX)

file(GLOB_RECURSE GUI_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_executable(${PROJECT_NAME} ${GUI_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${GUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Własna biblioteka silnika (OpenGLApp) — dostarcza transitive glfw/glew/assimp/imgui/glm
if(TARGET OpenGLApp)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGLApp)
endif()

# ImGui — GUI bezpośrednio korzysta z Dock* API i innych funkcji ImGui
if(TARGET imgui)
    target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    _UNICODE
    UNICODE
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Working directory zgodny ze starym $(ProjectDir) — config.h w OpenGLApp
# używa ścieżek "..\Assets\...", GUI/ leży obok OpenGLApp/, więc to trafia w root/Assets
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

if(TARGET stb_image_reader)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:stb_image_reader>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying stb_image_reader runtime to GUI directory"
    )
endif()