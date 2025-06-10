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