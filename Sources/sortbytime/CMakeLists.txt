add_executable(sortbytime main.cpp)
target_link_libraries(sortbytime PUBLIC reader)
set_target_properties(sortbytime PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")