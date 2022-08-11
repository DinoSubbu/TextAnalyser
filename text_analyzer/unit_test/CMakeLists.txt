file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "*.cpp")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(UnitTest ${Sources})

target_compile_options(UnitTest PRIVATE --coverage -O0 -g)
target_link_libraries(UnitTest PUBLIC
    ${GTEST_LIBRARIES} 
    pthread
    TextAnalyzer
    PRIVATE
        --coverage
)

add_test(
    NAME UnitTest
    COMMAND UnitTest
)