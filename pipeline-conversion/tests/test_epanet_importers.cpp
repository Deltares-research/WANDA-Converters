#include "mapping/from_epanet/epanet_model_importer.h"
#include "mapping/from_epanet/epanet_node_importer.h"
#include "mapping/from_epanet/epanet_pipe_importer.h"
#include "mapping/from_epanet/epanet_unit_converter.h"
#include <epanet2.h>
#include <epanet2_2.h>
#include <filesystem>
#include <gtest/gtest.h>

// ============================================================
// EpanetImporter integration tests (require test_model.inp)
// ============================================================

class EpanetImporterTest : public ::testing::Test {
protected:
  std::filesystem::path test_file =
      std::filesystem::path(__FILE__).parent_path().parent_path() /
      "test_data" / "test_model.inp";

  bool file_available() const { return std::filesystem::exists(test_file); }
};

TEST_F(EpanetImporterTest, ImportsNetworkFromFile) {
  if (!file_available())
    GTEST_SKIP() << "test_model.inp not found";

  EpanetImporter importer(test_file.string());
  Network network = importer.import();

  // The file should produce at least some nodes and pipes
  EXPECT_GT(network.nodes.size(), 0);
  EXPECT_GT(network.pipes.size(), 0);
}

TEST_F(EpanetImporterTest, PipesHaveValidConnectivity) {
  if (!file_available())
    GTEST_SKIP() << "test_model.inp not found";

  EpanetImporter importer(test_file.string());
  Network network = importer.import();

  for (const auto &pipe : network.pipes) {
    EXPECT_FALSE(pipe.name.empty());
    EXPECT_FALSE(pipe.from_node_id.empty());
    EXPECT_FALSE(pipe.to_node_id.empty());
    EXPECT_GT(pipe.length, 0.0);
    EXPECT_GT(pipe.inner_diameter, 0.0);
  }
}

TEST_F(EpanetImporterTest, NodesHaveIds) {
  if (!file_available())
    GTEST_SKIP() << "test_model.inp not found";

  EpanetImporter importer(test_file.string());
  Network network = importer.import();

  for (const auto &node : network.nodes) {
    EXPECT_FALSE(node.id.empty());
  }
}

// ============================================================
// EpanetPipeImporter unit test with a real project
// ============================================================

TEST_F(EpanetImporterTest, PipeImporterReturnsPipeWithCorrectFields) {
  if (!file_available())
    GTEST_SKIP() << "test_model.inp not found";

  EN_Project ph;
  EN_createproject(&ph);
  EN_open(ph, test_file.string().c_str(), "", "");

  int flow_units = 0;
  EN_getflowunits(ph, &flow_units);
  double hlf = 0;
  EN_getoption(ph, EN_HEADLOSSFORM, &hlf);
  EpanetUnitConverter uc(flow_units, static_cast<int>(hlf));

  EpanetPipeImporter pipe_importer;
  // Find first pipe link
  int link_count = 0;
  EN_getcount(ph, EN_LINKCOUNT, &link_count);
  ASSERT_GT(link_count, 0);

  for (int i = 1; i <= link_count; ++i) {
    int lt = 0;
    EN_getlinktype(ph, i, &lt);
    if (lt == EN_PIPE) {
      Pipe p = pipe_importer.import(ph, i, uc);
      EXPECT_FALSE(p.name.empty());
      EXPECT_GT(p.length, 0.0);
      EXPECT_GT(p.inner_diameter, 0.0);
      break;
    }
  }

  EN_close(ph);
  EN_deleteproject(ph);
}

// ============================================================
// EpanetNodeImporter unit test with a real project
// ============================================================

TEST_F(EpanetImporterTest, NodeImporterReturnsNodeWithCorrectFields) {
  if (!file_available())
    GTEST_SKIP() << "test_model.inp not found";

  EN_Project ph;
  EN_createproject(&ph);
  EN_open(ph, test_file.string().c_str(), "", "");

  int flow_units = 0;
  EN_getflowunits(ph, &flow_units);
  double hlf = 0;
  EN_getoption(ph, EN_HEADLOSSFORM, &hlf);
  EpanetUnitConverter uc(flow_units, static_cast<int>(hlf));

  EpanetNodeImporter node_importer;
  int node_count = 0;
  EN_getcount(ph, EN_NODECOUNT, &node_count);
  ASSERT_GT(node_count, 0);

  Node n = node_importer.import(ph, 1, uc);
  EXPECT_FALSE(n.id.empty());

  EN_close(ph);
  EN_deleteproject(ph);
}
