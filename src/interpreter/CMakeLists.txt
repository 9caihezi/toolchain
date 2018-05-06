add_executable(interpreter main.cpp)
add_executable(program_state_test program_state_test.cpp)
add_executable(program_test program_test.cpp)
# add_executable(interpreter_test interpreter_test.cpp)

add_library(interpreter_lib program_state.h program_state.cpp program.h program.cpp)
target_link_libraries(interpreter interpreter_lib)
target_link_libraries(program_state_test interpreter_lib gtest_main)
target_link_libraries(program_test interpreter_lib gtest_main)

add_test(program_state_test program_state_test --gtest_color=yes)
add_test(program_test program_test --gtest_color=yes)
