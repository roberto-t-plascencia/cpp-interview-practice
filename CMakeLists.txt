cmake_minimum_required(VERSION 3.20)
project(cpp_interview_practice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OFF (default): tests compile against YOUR code in problems/.
# ON: tests compile against the reference answers in solutions/.
option(PRACTICE_USE_SOLUTIONS "Build tests against the reference solutions" OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
  GIT_SHALLOW    TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # needed for MSVC
FetchContent_MakeAvailable(googletest)

if(PRACTICE_USE_SOLUTIONS)
  set(PRACTICE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/solutions)
  message(STATUS "Testing reference solutions")
else()
  set(PRACTICE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/problems)
  message(STATUS "Testing your solutions in problems/")
endif()

enable_testing()
include(GoogleTest)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*_test.cpp)
foreach(test_src ${TEST_SOURCES})
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  target_include_directories(${test_name} PRIVATE ${PRACTICE_INCLUDE_DIR})
  target_link_libraries(${test_name} PRIVATE GTest::gtest_main)
  if(MSVC)
    target_compile_options(${test_name} PRIVATE /W4 /permissive-)
  else()
    target_compile_options(${test_name} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
  gtest_discover_tests(${test_name} DISCOVERY_TIMEOUT 30)
endforeach()
