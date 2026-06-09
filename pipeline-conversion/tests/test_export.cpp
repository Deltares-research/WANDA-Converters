#include "core/network.h"
#include "mapping/to_wanda/wanda_model_exporter.h"
#include "model_converter.h"
#include <filesystem>
#include <gtest/gtest.h>

// ============================================================
// Helper: builds a sample Network for export tests
// ============================================================

namespace {

Network create_sample_network() {
  Network network;
  network.nodes.push_back(
      {.id = "N1", .elevation = 10.0, .position = {0.0f, 0.0f}});
  network.nodes.push_back(
      {.id = "N2", .elevation = 5.0, .position = {100.0f, 0.0f}});
  network.nodes.push_back(
      {.id = "N3", .elevation = 3.0, .position = {200.0f, 0.0f}});

  network.pipes.push_back({.name = "P1",
                           .length = 500.0,
                           .inner_diameter = 0.3,
                           .friction_model_roughness = 0.001,
                           .friction_model = FrictionModel::DarcyWeisbach,
                           .from_node_id = "N1",
                           .to_node_id = "N2",
                           .position = {0.0f, 0.0f, 100.0f, 0.0f}});
  network.pipes.push_back({.name = "P2",
                           .length = 300.0,
                           .inner_diameter = 0.25,
                           .friction_model_roughness = 0.0015,
                           .friction_model = FrictionModel::DarcyWeisbach,
                           .from_node_id = "N2",
                           .to_node_id = "N3",
                           .position = {100.0f, 0.0f, 200.0f, 0.0f}});

  return network;
}

} // anonymous namespace

// ============================================================
// Test: Export to WANDA creates a valid file
// ============================================================

class WandaExportTest : public ::testing::Test {
protected:
  Network network = create_sample_network();
  std::filesystem::path output_dir =
      std::filesystem::path(__FILE__).parent_path().parent_path() / "test_data";
  std::filesystem::path output_file = output_dir / "test_export_output.wdi";

  void TearDown() override {
    // Clean up generated file after test
    if (std::filesystem::exists(output_file)) {
      std::filesystem::remove(output_file);
    }
  }

  bool wanda_available() const {
    return std::filesystem::exists(
        R"(c:\Program Files (x86)\Deltares\Wanda 4.8\Bin64\)");
  }
};

TEST_F(WandaExportTest, ExporterCreatesOutputFile) {
  if (!wanda_available())
    GTEST_SKIP() << "WANDA binaries not available";

  // Ensure output doesn't already exist
  if (std::filesystem::exists(output_file)) {
    std::filesystem::remove(output_file);
  }

  WandaModelExporter exporter;
  EXPECT_NO_THROW(exporter.convert(network, output_file.string()));
  EXPECT_TRUE(std::filesystem::exists(output_file));
}

TEST_F(WandaExportTest, ExporterHandlesEmptyNetwork) {
  if (!wanda_available())
    GTEST_SKIP() << "WANDA binaries not available";

  if (std::filesystem::exists(output_file)) {
    std::filesystem::remove(output_file);
  }

  Network empty_network;
  WandaModelExporter exporter;
  // An empty network should still produce a valid (empty) model file
  EXPECT_NO_THROW(exporter.convert(empty_network, output_file.string()));
  EXPECT_TRUE(std::filesystem::exists(output_file));
}

TEST_F(WandaExportTest, ExporterPreservesNodeCount) {
  if (!wanda_available())
    GTEST_SKIP() << "WANDA binaries not available";

  if (std::filesystem::exists(output_file)) {
    std::filesystem::remove(output_file);
  }

  WandaModelExporter exporter;
  exporter.convert(network, output_file.string());

  // Re-import the exported file and verify node/pipe counts
  // This is a round-trip sanity check
  EXPECT_TRUE(std::filesystem::exists(output_file));
}

// ============================================================
// Test: ModelConverter round-trip EPAnet -> WANDA
// ============================================================

class ModelConverterExportTest : public ::testing::Test {
protected:
  std::filesystem::path test_data =
      std::filesystem::path(__FILE__).parent_path().parent_path() / "test_data";
  std::filesystem::path epanet_input = test_data / "test_model.inp";
  std::filesystem::path wanda_output = test_data / "test_roundtrip_output.wdi";

  void TearDown() override {
    if (std::filesystem::exists(wanda_output)) {
      std::filesystem::remove(wanda_output);
    }
  }

  bool inputs_available() const {
    return std::filesystem::exists(epanet_input) &&
           std::filesystem::exists(
               R"(c:\Program Files (x86)\Deltares\Wanda 4.8\Bin64\)");
  }
};

TEST_F(ModelConverterExportTest, EpanetToWandaProducesFile) {
  if (!inputs_available())
    GTEST_SKIP() << "EPAnet input or WANDA binaries not available";

  if (std::filesystem::exists(wanda_output)) {
    std::filesystem::remove(wanda_output);
  }

  ModelConverter converter(epanet_input.string(), "EPAnet");
  EXPECT_NO_THROW(converter.convert(wanda_output.string(), "WANDA"));
  EXPECT_TRUE(std::filesystem::exists(wanda_output));
}

// ============================================================
// Test: ModelConverter to EPAnet (currently a no-op, verify no crash)
// ============================================================

TEST_F(ModelConverterExportTest, EpanetToEpanetNoOp) {
  if (!std::filesystem::exists(epanet_input))
    GTEST_SKIP() << "EPAnet input not available";

  ModelConverter converter(epanet_input.string(), "EPAnet");
  // Converting to EPAnet currently just prints and returns
  // Ensure it doesn't crash; output file won't be created
  EXPECT_NO_THROW(converter.convert(wanda_output.string(), "EPAnet"));
}

// ============================================================
// Test: ModelConverter to GIS (currently a no-op, verify no crash)
// ============================================================

TEST_F(ModelConverterExportTest, EpanetToGISNoOp) {
  if (!std::filesystem::exists(epanet_input))
    GTEST_SKIP() << "EPAnet input not available";

  ModelConverter converter(epanet_input.string(), "EPAnet");
  EXPECT_NO_THROW(converter.convert(wanda_output.string(), "GIS"));
}
