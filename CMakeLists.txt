cmake_minimum_required(VERSION 3.15)
project(luffy VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries (.so/.dll) instead of static (.a/.lib)" ON)
option(LUFFY_ENABLE_GRAPHICS "Enable OpenGL/GLFW components" OFF)

include_directories(include)

set(LUFFY_CORE_SOURCES
    # TODO: Add source files here
    src/test.c
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

if(LUFFY_ENABLE_GRAPHICS)
    target_link_libraries(luffy PRIVATE glfw)
endif()

install(DIRECTORY include/luffy DESTINATION include)
install(TARGETS luffy
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

# Add tests
# if(LUFFY_ENABLE_GRAPHICS)
#     enable_testing()
#     add_subdirectory(tests_graphics)
# endif()

enable_testing()
add_subdirectory(tests)
