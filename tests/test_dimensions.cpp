#include <gtest/gtest.h>

#include "Dimensions/Dimensions.hpp"

// Use a concrete implementation of the Dimensions CRTP base class for testing.
// This class provides simple, known values for the base scales.
class MyUnitSystem
    : public Dimensions::MechanicalMassDimensions<MyUnitSystem, double> {
 public:
  // Define the required base scales for the MechanicalMassDimensions helper.
  constexpr double LengthScale() const noexcept { return 2.0; }  // L
  constexpr double MassScale() const noexcept { return 3.0; }    // M
  constexpr double TimeScale() const noexcept { return 4.0; }    // T
};

// Test fixture for our unit system
class DimensionsTest : public ::testing::Test {
 protected:
  MyUnitSystem unit_system;
};

// Test that the base scales are correctly retrieved.
TEST_F(DimensionsTest, BaseScalesAreCorrect) {
  EXPECT_EQ(unit_system.LengthScale(), 2.0);
  EXPECT_EQ(unit_system.MassScale(), 3.0);
  EXPECT_EQ(unit_system.TimeScale(), 4.0);
  EXPECT_EQ(unit_system.TemperatureScale(), 1.0);  // From MechanicalDimensions
}

// Test the derived DensityScale, which is a key calculation in the helper
// class.
TEST_F(DimensionsTest, DensityScaleIsCorrect) {
  // Density = M / L^3 = 3.0 / (2.0 * 2.0 * 2.0) = 3.0 / 8.0 = 0.375
  EXPECT_DOUBLE_EQ(unit_system.DensityScale(), 0.375);
}

// Test various other derived scales to ensure calculations are correct.
TEST_F(DimensionsTest, DerivedScalesAreCorrect) {
  // Velocity = L / T = 2.0 / 4.0 = 0.5
  EXPECT_DOUBLE_EQ(unit_system.VelocityScale(), 0.5);

  // Acceleration = V / T = 0.5 / 4.0 = 0.125
  EXPECT_DOUBLE_EQ(unit_system.AccelerationScale(), 0.125);

  // Force = M * A = 3.0 * 0.125 = 0.375
  EXPECT_DOUBLE_EQ(unit_system.ForceScale(), 0.375);

  // Energy = M * V^2 = 3.0 * (0.5 * 0.5) = 3.0 * 0.25 = 0.75
  EXPECT_DOUBLE_EQ(unit_system.EnergyScale(), 0.75);
}

// Test the calculation of dimensionless constants.
TEST_F(DimensionsTest, DimensionlessConstantsAreCorrect) {
  const double G_si = 6.67430e-11;
  const double density_scale = 0.375;
  const double time_scale = 4.0;

  // G' = G * rho * T^2
  const double expected_dimensionless_G =
      G_si * density_scale * time_scale * time_scale;
  EXPECT_DOUBLE_EQ(unit_system.GravitationalConstant(),
                   expected_dimensionless_G);
}
