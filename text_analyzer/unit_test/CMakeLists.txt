project(UnitTest)

set(TEST_FILE TextAnalyzer_test.cpp)
set(SOURCE_FILE 
    ../src/TextAnalyzer.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set_source_files_properties(${SOURCE_FILE} PROPERTIES LANGUAGE CXX COMPILE_FLAGS ${CXXFLAGS} "-std=c++17 -g -O0 -coverage -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${TEST_FILE})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${GTEST_LIBRARIES} 
    pthread
    TextAnalyzer
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)