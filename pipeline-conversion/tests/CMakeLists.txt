add_executable(pipeline_smoke_tests
  test_smoke.cpp
)

target_link_libraries(pipeline_smoke_tests
  PRIVATE
    GTest::gtest_main
    pipeline_core
    pipeline_mapping
    pipeline_descriptors
    pipeline_builders
    pipeline_utils
)

include(GoogleTest)
gtest_discover_tests(pipeline_smoke_tests)
