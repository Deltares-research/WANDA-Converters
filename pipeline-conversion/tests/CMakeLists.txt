add_executable(pipeline_smoke_tests
  test_smoke.cpp
)

target_link_libraries(pipeline_smoke_tests
  PRIVATE
    GTest::gtest_main
    pipeline_conversion
)

include(GoogleTest)
gtest_discover_tests(pipeline_smoke_tests)
