SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_TLS_VERIFY 0)

include_directories(tests)
include_directories(./)

SET(SOURCE_FILES
        InMemoryHistory.cpp
        SimpleCalculator.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

SET(SOURCE_TEST_FILES
        tests/test_SimpleCalculator.cpp
        tests/test_InMemoryHistory.cpp
)

add_executable(test_${PROJECT_NAME} ${SOURCE_FILES} ${SOURCE_TEST_FILES})
target_link_libraries(test_${PROJECT_NAME} PRIVATE GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME})