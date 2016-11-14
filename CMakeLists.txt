cmake_minimum_required(VERSION 2.8.2)

project(rapidcheck_test1 CXX)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(NOT COMPILER_SUPPORTS_CXX14)
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
download_project(PROJ                rapidcheck
                 GIT_REPOSITORY      https://github.com/emil-e/rapidcheck
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${rapidcheck_SOURCE_DIR} ${rapidcheck_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

###########################################################

include(CTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(custom SHARED src/person.cpp)
target_include_directories(custom PRIVATE src/)

function(define_test TEST_NAME TEST_DESCRIPTION SOURCE_LIST)
  add_executable(${TEST_NAME} ${SOURCE_LIST})
  target_include_directories(${TEST_NAME} PRIVATE src/)
  target_include_directories(${TEST_NAME} PRIVATE ${rapidcheck_SOURCE_DIR}/include)
  target_include_directories(${TEST_NAME} PRIVATE ${rapidcheck_SOURCE_DIR}/extras/gtest/include)
  target_link_libraries(${TEST_NAME} gtest gmock_main rapidcheck custom)
  add_test(NAME ${TEST_DESCRIPTION} COMMAND ${TEST_NAME})
endfunction()

define_test(test_add    rapidcheck_add                    test/gtest1.cpp)
define_test(test_vector rapidcheck_double_vector_reversal test/reverse_vector.cpp)
define_test(test_person rapidcheck_person                 test/person_test.cpp)
