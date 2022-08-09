project(TextAnalyzer)

if(UNIT_TESTING)
    add_subdirectory(unit_test)
    return()
endif()

include_directories(include)

set(SRC_FILES
    src/TextAnalyzer.cpp)

add_library(${PROJECT_NAME} ${SRC_FILES})

#target_link_libraries(
 #   ${PROJECT}
  #  PRIVATE
    #
    #)

