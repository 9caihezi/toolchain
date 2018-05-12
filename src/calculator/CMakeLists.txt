add_executable(calculator main.cpp) 
add_executable(tokenizer_test tokenizer_test.cpp) 

add_library(tokenizer_lib tokenizer.h tokenizer.cpp) 
target_link_libraries(calculator tokenizer_lib) 
target_link_libraries(tokenizer_test tokenizer_lib gtest_main gmock)
 
add_test(tokenizer_test tokenizer_test --gtest_color=yes)
