#pragma once

#include <cmath>
#include <numbers>

#include "NumericConcepts/Functions.hpp"
#include "NumericConcepts/Numeric.hpp"

namespace Dimensions {

struct TimeScaleSet {};
struct TimeScaleNotSet {};

template <typename T>
concept TimeScaleOption =
    std::same_as<T, TimeScaleSet> || std::same_as<T, TimeScaleNotSet>;

template <typename _Derived, TimeScaleOption Option = TimeScaleSet>
class Dimensions {
private:
  const long double _gravitationalConstant =
      static_cast<long double>(6.67430e-11);

public:
  // Defined methods in the derived class.
  constexpr auto LengthScale() const { return Derived().LengthScale(); }
  constexpr auto DensityScale() const { return Derived().DensityScale(); }
  constexpr auto TimeScale() const {
    if constexpr (std::same_as<Option, TimeScaleNotSet>) {
      using Real = decltype(DensityScale());
      return static_cast<Real>(1) /
             std::sqrt(std::numbers::pi_v<Real> * _gravitationalConstant *
                       DensityScale());
    } else {
      return Derived().TimeScale();
    }
  }

  // Implied methods.
  constexpr auto GravitationalConstant() const {
    return _gravitationalConstant * DensityScale() * std::pow(TimeScale(), 2);
  }

  constexpr auto MassScale() const {
    return DensityScale() * std::pow(LengthScale(), 3);
  }

  constexpr auto VelocityScale() const { return LengthScale() / TimeScale(); }

  constexpr auto AccelerationScale() const {
    return VelocityScale() / TimeScale();
  }

  constexpr auto ForceScale() const {
    return MassScale() * AccelerationScale();
  }

  constexpr auto TractionScale() const {
    return ForceScale() / std::pow(LengthScale(), 2);
  }

  constexpr auto MomentScale() const {
    return ForceScale() * std::pow(LengthScale(), 2);
  }

  constexpr auto PotentialScale() const {
    return AccelerationScale() * LengthScale();
  }

private:
  constexpr auto &Derived() const {
    return static_cast<const _Derived &>(*this);
  }
  constexpr auto &Derived() { return static_cast<_Derived &>(*this); }
};

} // namespace Dimensions