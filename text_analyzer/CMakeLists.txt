project(TextAnalyzer CXX)

enable_testing()

include_directories(
    include
    )

set(SRC_FILES
    src/TextAnalyzer.cpp)

add_library(${PROJECT_NAME} ${SRC_FILES})

add_subdirectory(unit_test)

