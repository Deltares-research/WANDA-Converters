#include "core/network.h"
#include "core/node.h"
#include "core/pipe.h"
#include <gtest/gtest.h>

// ============================================================
// Node tests
// ============================================================

TEST(NodeTest, DefaultConstruction) {
  Node node{};
  EXPECT_TRUE(node.id.empty());
  EXPECT_EQ(node.elevation, 0.0);
  EXPECT_TRUE(node.position.empty());
}

TEST(NodeTest, DesignatedInitializer) {
  Node node{.id = "N1", .elevation = 10.5, .position = {1.0f, 2.0f}};
  EXPECT_EQ(node.id, "N1");
  EXPECT_DOUBLE_EQ(node.elevation, 10.5);
  ASSERT_EQ(node.position.size(), 2);
  EXPECT_FLOAT_EQ(node.position.x, 1.0f);
  EXPECT_FLOAT_EQ(node.position.y, 2.0f);
}

// ============================================================
// Pipe tests
// ============================================================

TEST(PipeTest, DefaultConstruction) {
  Pipe pipe{};
  EXPECT_TRUE(pipe.name.empty());
  EXPECT_DOUBLE_EQ(pipe.length, 0.0);
  EXPECT_DOUBLE_EQ(pipe.inner_diameter, 0.0);
  EXPECT_DOUBLE_EQ(pipe.friction_model_roughness, 0.0);
  EXPECT_EQ(pipe.friction_model, FrictionModel::DarcyWeisbach);
  EXPECT_TRUE(pipe.from_node_id.empty());
  EXPECT_TRUE(pipe.to_node_id.empty());
  EXPECT_TRUE(pipe.position.empty());
}

TEST(PipeTest, DesignatedInitializer) {
  Pipe pipe{.name = "P1",
            .length = 100.0,
            .inner_diameter = 0.5,
            .friction_model_roughness = 0.001,
            .friction_model = FrictionModel::HazenWilliams,
            .from_node_id = "N1",
            .to_node_id = "N2",
            .position = {0.0f, 0.0f}};
  EXPECT_EQ(pipe.name, "P1");
  EXPECT_DOUBLE_EQ(pipe.length, 100.0);
  EXPECT_DOUBLE_EQ(pipe.inner_diameter, 0.5);
  EXPECT_DOUBLE_EQ(pipe.friction_model_roughness, 0.001);
  EXPECT_EQ(pipe.friction_model, FrictionModel::HazenWilliams);
  EXPECT_EQ(pipe.from_node_id, "N1");
  EXPECT_EQ(pipe.to_node_id, "N2");
}

TEST(PipeTest, FrictionModelValues) {
  // Ensure all enum values are distinct
  EXPECT_NE(static_cast<int>(FrictionModel::HazenWilliams),
            static_cast<int>(FrictionModel::DarcyWeisbach));
  EXPECT_NE(static_cast<int>(FrictionModel::DarcyWeisbach),
            static_cast<int>(FrictionModel::Manning));
  EXPECT_NE(static_cast<int>(FrictionModel::HazenWilliams),
            static_cast<int>(FrictionModel::Manning));
}

// ============================================================
// Network tests
// ============================================================

TEST(NetworkTest, DefaultConstruction) {
  Network network{};
  EXPECT_TRUE(network.nodes.empty());
  EXPECT_TRUE(network.pipes.empty());
}

TEST(NetworkTest, AddNodesAndPipes) {
  Network network{};
  network.nodes.push_back({.id = "N1", .elevation = 5.0, .position = {0, 0}});
  network.nodes.push_back({.id = "N2", .elevation = 3.0, .position = {1, 0}});
  network.pipes.push_back({.name = "P1",
                           .length = 50.0,
                           .inner_diameter = 0.3,
                           .friction_model_roughness = 0.0015,
                           .from_node_id = "N1",
                           .to_node_id = "N2",
                           .position = {0, 0}});

  EXPECT_EQ(network.nodes.size(), 2);
  EXPECT_EQ(network.pipes.size(), 1);
  EXPECT_EQ(network.pipes[0].from_node_id, "N1");
  EXPECT_EQ(network.pipes[0].to_node_id, "N2");
}
