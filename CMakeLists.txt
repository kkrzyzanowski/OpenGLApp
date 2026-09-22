cmake_minimum_required(VERSION 3.14)
project(OpenGLAppSolution VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

option(BUILD_SHARED_DEPS "Build external deps as shared" OFF)

include(FetchContent)

# GLM (header-only)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# GLFW 3.2.1
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.2.1
)
FetchContent_MakeAvailable(glfw)

# GLEW 2.1.0
FetchContent_Declare(
  glew
  URL https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.zip
  SOURCE_SUBDIR build/cmake
)
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_STATIC ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glew)

# Assimp 4.1.0
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG v4.1.0
)
FetchContent_MakeAvailable(assimp)

# ImGui — brak CMakeLists w repo, budujemy sami jako bibliotekę
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.89.7-docking
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw)
target_compile_features(imgui PUBLIC cxx_std_20)

# Podprojekty — KOLEJNOŚĆ WAŻNA:
# OpenGLApp (lib) musi istnieć przed GUI (linkuje ją),
# GUI (exe) musi istnieć przed Stb_image_reader (kopiuje DLL do jej katalogu)

add_subdirectory(Stb_image_reader)
add_subdirectory(OpenGLApp)
add_subdirectory(GUI)
add_subdirectory(DirectXApp)