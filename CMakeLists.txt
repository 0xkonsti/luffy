cmake_minimum_required(VERSION 3.15)
project(luffy VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries (.so/.dll) instead of static (.a/.lib)" OFF)
option(LUFFY_ENABLE_GRAPHICS "Enable OpenGL/GLFW components" OFF)
option(LUFFY_BUILD_TESTS "Build tests for the library" ON)

include_directories(include)

file(GLOB_RECURSE LUFFY_CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

if(LUFFY_ENABLE_GRAPHICS)
    # GLFW
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(libs/glfw)
    include_directories(libs/glfw/include)

    # GLAD
    set(GLAD_SOURCES libs/glad/src/glad.c)
    include_directories(libs/glad/include)

    list(APPEND LUFFY_CORE_SOURCES
            # TODO: Add graphics source files here
            ${GLAD_SOURCES}
    )

    add_definitions(-DLUFFY_ENABLE_GRAPHICS)
endif()

add_library(luffy ${LUFFY_CORE_SOURCES})
add_library(luffy::luffy ALIAS luffy)

target_include_directories(luffy PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(LUFFY_ENABLE_GRAPHICS)
    target_include_directories(luffy PUBLIC libs/glad/include libs/glfw/include)
    target_link_libraries(luffy PRIVATE glfw)
    target_compile_definitions(luffy PUBLIC LUFFY_ENABLE_GRAPHICS)
endif()

install(DIRECTORY include/ DESTINATION include)
install(TARGETS luffy
    EXPORT luffyTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(EXPORT luffyTargets
    FILE luffyConfig.cmake
    NAMESPACE luffy::
    DESTINATION lib/cmake/luffy
)

# Tests (optional)
if(LUFFY_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
