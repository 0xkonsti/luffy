# Test für option
add_executable(test_option
    types/test_option.c
    ../libs/unity/src/unity.c
)
target_include_directories(test_option PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/unity/src
)
add_test(NAME option_tests COMMAND test_option)

# Test für result
add_executable(test_result
    types/test_result.c
    ../libs/unity/src/unity.c
)
target_include_directories(test_result PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/unity/src
)
add_test(NAME result_tests COMMAND test_result)

# Test für string
add_executable(test_string
    types/test_string.c
    ../libs/unity/src/unity.c
)
target_include_directories(test_string PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/unity/src
)
target_link_libraries(test_string PRIVATE luffy)
add_test(NAME string_tests COMMAND test_string)
