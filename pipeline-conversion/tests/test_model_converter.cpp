#include "model_converter.h"
#include <filesystem>
#include <gtest/gtest.h>

// ============================================================
// ModelConverter constructor tests
// ============================================================

TEST(ModelConverterTest, ThrowsOnNonExistentFile) {
  EXPECT_THROW(ModelConverter("non_existent_file.inp", "EPAnet"),
               std::runtime_error);
}

TEST(ModelConverterTest, ThrowsOnUnsupportedInputType) {
  // Use any existing file for this test
  const auto test_file =
      std::filesystem::path(__FILE__).parent_path().parent_path() /
      "test_data" / "test_model.inp";
  if (std::filesystem::exists(test_file)) {
    EXPECT_THROW(ModelConverter(test_file.string(), "UnsupportedFormat"),
                 std::runtime_error);
  }
}

// ============================================================
// ModelConverter::convert tests
// ============================================================

TEST(ModelConverterTest, ConvertThrowsIfOutputFileExists) {
  const auto test_data =
      std::filesystem::path(__FILE__).parent_path().parent_path() / "test_data";
  const auto input_file = test_data / "test_model.inp";
  const auto existing_output = test_data / "test_model.inp"; // exists

  if (std::filesystem::exists(input_file)) {
    ModelConverter converter(input_file.string(), "EPAnet");
    EXPECT_THROW(converter.convert(existing_output.string(), "WANDA"),
                 std::runtime_error);
  }
}
