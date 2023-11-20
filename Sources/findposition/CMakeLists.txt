add_executable(findposition main.cpp)
target_link_libraries(findposition PUBLIC reader)
# set_target_properties(findposition PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")