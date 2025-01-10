#include "Dimensions/Dimensions.hpp"
#include "NumericConcepts/Numeric.hpp"
#include <iostream>

namespace NC = NumericConcepts;
using namespace NC;
using namespace Dimensions;

template <NC::Real Real>
class DimensionedClass : public Dimensions<DimensionedClass<Real>> {
public:
  // Define the necessary methods.
  constexpr auto LengthScale() const { return static_cast<Real>(6.371e6); }

  constexpr auto DensityScale() const { return static_cast<Real>(5.514e3); }

  constexpr auto TimeScale() const { return static_cast<Real>(1); }
};

template <NC::Real Real>
class DimensionedClassWithDefaultTimeScale
    : public Dimensions<DimensionedClassWithDefaultTimeScale<Real>,
                        TimeScaleNotSet> {
public:
  // Define the necessary methods.
  constexpr auto LengthScale() const { return static_cast<Real>(6.371e6); }

  constexpr auto DensityScale() const { return static_cast<Real>(5.514e3); }
};

int main() {

  auto d = DimensionedClass<double>();
  std::cout << d.LengthScale() << std::endl;
  std::cout << d.DensityScale() << std::endl;
  std::cout << d.TimeScale() << std::endl;
  std::cout << d.MassScale() << std::endl;
  std::cout << d.VelocityScale() << std::endl;
  std::cout << d.AccelerationScale() << std::endl;
  std::cout << d.ForceScale() << std::endl;
  std::cout << d.TractionScale() << std::endl;
  std::cout << d.MomentScale() << std::endl;
  std::cout << d.PotentialScale() << std::endl << std::endl;

  auto d2 = DimensionedClassWithDefaultTimeScale<double>();
  std::cout << d2.LengthScale() << std::endl;
  std::cout << d2.DensityScale() << std::endl;
  std::cout << d2.TimeScale() << std::endl;
  std::cout << d2.MassScale() << std::endl;
  std::cout << d2.VelocityScale() << std::endl;
  std::cout << d2.AccelerationScale() << std::endl;
  std::cout << d2.ForceScale() << std::endl;
  std::cout << d2.TractionScale() << std::endl;
  std::cout << d2.MomentScale() << std::endl;
  std::cout << d2.PotentialScale() << std::endl;
}