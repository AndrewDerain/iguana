cmake_minimum_required(VERSION 2.15)
project(iguana)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
add_compile_options(/utf-8)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -g -std=c++20")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif(MSVC)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(IGUANA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")

add_definitions(-DTHROW_UNKNOWN_KEY)

option(ENABLE_SEQUENTIAL_PARSE "parse json sequential more efficient if the json fields sequences are the same with struct fields" OFF)
if (${ENABLE_SEQUENTIAL_PARSE})
    ADD_DEFINITIONS(-DSEQUENTIAL_PARSE)
endif ()

option(HAS_RAPIDJSON "import rapidjson" OFF)
if (${HAS_RAPIDJSON})
	add_definitions(-DHAS_RAPIDJSON)
	include_directories(../rapidjson/include)
	ADD_DEFINITIONS(-DRAPIDJSON_HAS_STDSTRING)
endif()

option(HAS_RAPIDYAML "import rapidyaml" OFF)
if (${HAS_RAPIDYAML})
	add_definitions(-DHAS_RAPIDYAML)
endif()

include_directories(
	${IGUANA_DIR}
)


set(JSON_EXAMPLE
	example/json_example.cpp
)

set(XML_EXAMPLE
	example/xml_example.cpp
)
set(YAML_EXAMPLE
	example/yaml_example.cpp
)

set(TEST_SOME test/test.cpp)
set(TEST_UT test/unit_test.cpp)
set(TEST_JSON_FILES test/test_json_files.cpp)
set(TEST_XML test/test_xml.cpp)
set(JSONBENCHMARK benchmark/json_benchmark.cpp)
set(XMLBENCH  benchmark/xml_benchmark.cpp)
set(TEST_YAML test/test_yaml.cpp test/test_yaml_bech.cpp)
set(YAMLBENCH  benchmark/yaml_benchmark.cpp)
set(TEST_NOTHROW test/test_yaml_nothrow.cpp)
set(TEST_UTIL test/test_util.cpp)
set(TEST_XMLNOTHROW test/test_xml_nothrow.cpp)

add_executable(json_example 	${JSON_EXAMPLE})
add_executable(json_benchmark 	${JSONBENCHMARK})
add_executable(test_some	${TEST_SOME})
add_executable(test_ut 	${TEST_UT})
add_executable(test_json_files 	${TEST_JSON_FILES})
if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
    add_executable(xml_example 		${XML_EXAMPLE})
    add_executable(yaml_example 		${YAML_EXAMPLE})
    add_executable(test_xml ${TEST_XML})
    add_executable(xml_benchmark ${XMLBENCH})
    add_executable(test_yaml ${TEST_YAML})
    add_executable(yaml_benchmark ${YAMLBENCH})
    add_executable(test_nothrow ${TEST_NOTHROW})
    add_executable(test_util ${TEST_UTIL})
    add_executable(test_xml_nothrow ${TEST_XMLNOTHROW})
endif()

# unit test
option(BUILD_UNIT_TESTS "Build unit tests" ON)
if (BUILD_UNIT_TESTS)
    enable_testing()
endif ()

# coverage test
option(COVERAGE_TEST "Build with unit test coverage" OFF)
if(COVERAGE_TEST)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage --coverage")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    endif()
endif()

add_test(NAME test_some COMMAND test_some)
add_test(NAME test_ut COMMAND test_ut)
add_test(NAME test_json_files COMMAND test_json_files)
if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
    add_test(NAME test_xml COMMAND test_xml)
    add_test(NAME test_yaml COMMAND test_yaml)
    add_test(NAME test_nothrow COMMAND test_nothrow)
    add_test(NAME test_util COMMAND test_util)
    add_test(NAME test_xml_nothrow COMMAND test_xml_nothrow)
endif()