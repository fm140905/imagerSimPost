add_library(reader SHARED reader.cpp)

add_subdirectory(sortbyhist)
add_subdirectory(findposition)
add_subdirectory(sortbytime)
add_subdirectory(findCoincidences)
add_subdirectory(findCoincidencesHist)
add_subdirectory(ideal)

add_subdirectory(mergedc)