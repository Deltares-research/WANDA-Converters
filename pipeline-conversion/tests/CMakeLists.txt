add_executable(pipeline_tests
  test_smoke.cpp
  test_core.cpp
  test_epanet_unit_converter.cpp
  test_epanet_importers.cpp
  test_model_converter.cpp
  test_export.cpp
)

target_link_libraries(pipeline_tests
  PRIVATE
    GTest::gtest_main
    pipeline_conversion
)

include(GoogleTest)
gtest_discover_tests(pipeline_tests)
