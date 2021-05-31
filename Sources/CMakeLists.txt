add_library(reader SHARED reader.cpp)

add_executable(postproc main.cpp)
target_link_libraries(postproc PUBLIC reader)