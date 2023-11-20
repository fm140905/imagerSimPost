add_executable(readerTest test.cpp)
target_link_libraries(readerTest PUBLIC gtest_main) # reader)

add_test(
    NAME readerTest
    COMMAND readerTest
)
    