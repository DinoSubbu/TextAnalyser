cmake_minimum_required(VERSION 3.16.3)
project(main CXX)
set(CMAKE_CXX_STANDARD 17)
find_package(Boost 1.71 COMPONENTS PROGRAM_OPTIONS REQUIRED)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "Main.cpp")

include_directories(
    text_analyzer/include
    ${Boost_INCLUDE_DIR}
    )

add_subdirectory(text_analyzer)

add_executable(TextAnalyzerTool ${Sources})

target_link_libraries(TextAnalyzerTool PUBLIC
TextAnalyzer
Boost::program_options
)
