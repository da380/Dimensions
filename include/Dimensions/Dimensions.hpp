#pragma once

#include <cmath>
#include <numbers>

#include "NumericConcepts/Functions.hpp"
#include "NumericConcepts/Numeric.hpp"

namespace Dimensions {

template <typename T>
concept Dimensionable = requires(T t) {
  { t.LengthScale() } -> NumericConcepts::Real;
  { t.DensityScale() } -> NumericConcepts::Real;
  { t.TimeScale() } -> NumericConcepts::Real;
  { t.TemperatureScale() } -> NumericConcepts::Real;
  requires NumericConcepts::SamePrecision<
      decltype(t.LengthScale()), decltype(t.DensityScale()),
      decltype(t.TimeScale()), decltype(t.TemperatureScale())>;
};

template <typename _Derived> class Dimensions {
private:
  const long double _gravitationalConstant =
      static_cast<long double>(6.67430e-11);

  const long double _boltzmannConstant = static_cast<long double>(1.380649e-23);

public:
  // Defined methods in the derived class.
  constexpr auto LengthScale() const { return Derived().LengthScale(); }
  constexpr auto DensityScale() const { return Derived().DensityScale(); }
  constexpr auto TimeScale() const { return Derived().TimeScale(); }
  constexpr auto TemperatureScale() const {
    return Derived().TemperatureScale();
  }

  // Implied methods.
  constexpr auto GravitationalConstant() const {
    return _gravitationalConstant * DensityScale() * std::pow(TimeScale(), 2);
  }

  constexpr auto BoltzmannConstant() const {
    return _boltzmannConstant * TemperatureScale() / EnergyScale();
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

  constexpr auto EnergyScale() const {
    return MassScale() * std::pow(VelocityScale(), 2);
  }

private:
  constexpr Dimensionable auto &Derived() const {
    return static_cast<const _Derived &>(*this);
  }
  constexpr Dimensionable auto &Derived() {
    return static_cast<_Derived &>(*this);
  }
};

} // namespace Dimensions