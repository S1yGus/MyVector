cmake_minimum_required(VERSION 3.14)

set(ProjectName MyVector)

project(${ProjectName})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(HEADERS
	src/myvector.h)

set(SOURCES
	src/main.cpp)

set(TEST_SOURCES
	test/test.cpp)

add_executable(${ProjectName} ${HEADERS} ${SOURCES})

add_executable(test_myvector ${TEST_SOURCES})

target_link_libraries(
  test_myvector
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_myvector)

set_target_properties(${ProjectName} PROPERTIES
	CXX_STANDART 11
	CXX_STANDART_REQUIRED ON
)