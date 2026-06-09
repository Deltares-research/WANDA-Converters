#include "mapping/from_epanet/epanet_unit_converter.h"
#include <epanet2.h>
#include <gtest/gtest.h>

// ============================================================
// EpanetUnitConverter tests - SI unit system (EN_LPS)
// ============================================================

class EpanetUnitConverterSITest : public ::testing::Test {
protected:
  // EN_LPS = SI system, EN_DW = Darcy-Weisbach
  EpanetUnitConverter converter{EN_LPS, EN_DW};
};

TEST_F(EpanetUnitConverterSITest, LengthAlreadyMeters) {
  EXPECT_DOUBLE_EQ(converter.convert_length_to_si(100.0), 100.0);
}

TEST_F(EpanetUnitConverterSITest, DiameterMmToMeters) {
  // SI diameters are in mm, should convert to m
  EXPECT_DOUBLE_EQ(converter.convert_diameter_to_si(200.0), 0.2);
}

TEST_F(EpanetUnitConverterSITest, FlowLpsToM3s) {
  // 1 LPS = 0.001 m3/s
  EXPECT_DOUBLE_EQ(converter.convert_flow_to_si(1.0), 0.001);
}

TEST_F(EpanetUnitConverterSITest, RoughnessDW_MetersToMeters) {
  // DW roughness in SI is in mm (same as length factor applied)
  // length_factor_ = 1.0 for SI, so roughness_factor_ = 1.0
  EXPECT_DOUBLE_EQ(converter.convert_roughness_to_si(0.5), 0.5);
}

// ============================================================
// EpanetUnitConverter tests - US Customary (EN_GPM)
// ============================================================

class EpanetUnitConverterUSTest : public ::testing::Test {
protected:
  // EN_GPM = US system, EN_DW = Darcy-Weisbach
  EpanetUnitConverter converter{EN_GPM, EN_DW};
};

TEST_F(EpanetUnitConverterUSTest, LengthFeetToMeters) {
  EXPECT_NEAR(converter.convert_length_to_si(1.0), 0.3048, 1e-6);
}

TEST_F(EpanetUnitConverterUSTest, DiameterInchesToMeters) {
  EXPECT_NEAR(converter.convert_diameter_to_si(1.0), 0.0254, 1e-6);
}

TEST_F(EpanetUnitConverterUSTest, FlowGpmToM3s) {
  EXPECT_NEAR(converter.convert_flow_to_si(1.0), 0.0000630902, 1e-8);
}

TEST_F(EpanetUnitConverterUSTest, RoughnessDW_FeetToMeters) {
  // DW roughness converts with length factor (ft -> m)
  EXPECT_NEAR(converter.convert_roughness_to_si(1.0), 0.3048, 1e-6);
}

// ============================================================
// EpanetUnitConverter tests - Hazen-Williams (roughness is unitless)
// ============================================================

TEST(EpanetUnitConverterHWTest, RoughnessIsUnitless) {
  EpanetUnitConverter converter{EN_GPM, EN_HW};
  EXPECT_DOUBLE_EQ(converter.convert_roughness_to_si(130.0), 130.0);
}

TEST(EpanetUnitConverterHWTest, RoughnessIsUnitlessSI) {
  EpanetUnitConverter converter{EN_CMS, EN_HW};
  EXPECT_DOUBLE_EQ(converter.convert_roughness_to_si(130.0), 130.0);
}

// ============================================================
// EpanetUnitConverter tests - Manning (roughness is unitless)
// ============================================================

TEST(EpanetUnitConverterManningTest, RoughnessIsUnitless) {
  EpanetUnitConverter converter{EN_GPM, EN_CM};
  EXPECT_DOUBLE_EQ(converter.convert_roughness_to_si(0.013), 0.013);
}

// ============================================================
// EpanetUnitConverter tests - Various flow unit systems
// ============================================================

TEST(EpanetUnitConverterFlowTest, CMS) {
  EpanetUnitConverter converter{EN_CMS, EN_DW};
  EXPECT_DOUBLE_EQ(converter.convert_flow_to_si(1.0), 1.0);
}

TEST(EpanetUnitConverterFlowTest, LPM) {
  EpanetUnitConverter converter{EN_LPM, EN_DW};
  EXPECT_NEAR(converter.convert_flow_to_si(60.0), 0.001, 1e-9);
}

TEST(EpanetUnitConverterFlowTest, CMH) {
  EpanetUnitConverter converter{EN_CMH, EN_DW};
  EXPECT_NEAR(converter.convert_flow_to_si(3600.0), 1.0, 1e-9);
}

TEST(EpanetUnitConverterFlowTest, CFS) {
  EpanetUnitConverter converter{EN_CFS, EN_DW};
  EXPECT_NEAR(converter.convert_flow_to_si(1.0), 0.0283168, 1e-7);
}
