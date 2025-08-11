#pragma once

#include <cmath>

/**
 * @file Dimensions.hpp
 * @brief Defines a C++ framework for compile-time dimensional analysis.
 * @author David Al-Attar
 * @date August 2025
 */

namespace Dimensions {

/**
 * @brief A base class for dimensional analysis using the CRTP pattern.
 *
 * @details This class provides a framework for defining a system of units. A
 * user must create a derived class that implements the four base scales. This
 * class then uses those scales to automatically derive scaling factors for
 * other physical quantities.
 *
 * @tparam Derived_ The concrete derived class that implements the base scales.
 * @tparam Real_ The floating-point type for calculations (e.g., float, double).
 */
template <typename Derived_, typename Real_ = double>
class Dimensions {
 private:
  const Real_ gravitationalConstant_ = static_cast<Real_>(6.67430e-11);
  const Real_ boltzmannConstant_ = static_cast<Real_>(1.380649e-23);

 public:
  /** @name Base Scale Interface
   * Methods that must be implemented by the inheriting class.
   * @{
   */

  /**
   * @brief Retrieves the base length scale from the derived class.
   * @return The length scaling factor.
   */
  constexpr auto LengthScale() const noexcept {
    return Derived().LengthScale();
  }

  /**
   * @brief Retrieves the base density scale from the derived class.
   * @return The density scaling factor.
   */
  constexpr auto DensityScale() const noexcept {
    return Derived().DensityScale();
  }

  /**
   * @brief Retrieves the base time scale from the derived class.
   * @return The time scaling factor.
   */
  constexpr auto TimeScale() const noexcept { return Derived().TimeScale(); }

  /**
   * @brief Retrieves the base temperature scale from the derived class.
   * @return The temperature scaling factor.
   */
  constexpr auto TemperatureScale() const noexcept {
    return Derived().TemperatureScale();
  }
  /** @} */

  /** @name Derived Scales and Dimensionless Constants
   * Methods that are automatically derived from the base scales.
   * @{
   */

  /**
   * @brief Calculates the dimensionless Gravitational Constant (G) in this
   * system.
   * @return The dimensionless value of G.
   */
  constexpr auto GravitationalConstant() const noexcept {
    const auto t_scale = TimeScale();
    return gravitationalConstant_ * DensityScale() * t_scale * t_scale;
  }

  /**
   * @brief Calculates the dimensionless Boltzmann Constant (kB) in this system.
   * @return The dimensionless value of kB.
   */
  constexpr auto BoltzmannConstant() const noexcept {
    return boltzmannConstant_ * TemperatureScale() / EnergyScale();
  }

  /**
   * @brief Calculates the scaling factor for mass.
   * @return The derived mass scaling factor.
   */
  constexpr auto MassScale() const noexcept {
    const auto l_scale = LengthScale();
    return DensityScale() * l_scale * l_scale * l_scale;
  }

  /**
   * @brief Calculates the scaling factor for velocity.
   * @return The derived velocity scaling factor.
   */
  constexpr auto VelocityScale() const noexcept {
    return LengthScale() / TimeScale();
  }

  /**
   * @brief Calculates the scaling factor for acceleration.
   * @return The derived acceleration scaling factor.
   */
  constexpr auto AccelerationScale() const noexcept {
    return VelocityScale() / TimeScale();
  }

  /**
   * @brief Calculates the scaling factor for force.
   * @return The derived force scaling factor.
   */
  constexpr auto ForceScale() const noexcept {
    return MassScale() * AccelerationScale();
  }

  /**
   * @brief Calculates the scaling factor for traction (pressure/stress).
   * @return The derived traction scaling factor.
   */
  constexpr auto TractionScale() const noexcept {
    const auto l_scale = LengthScale();
    return ForceScale() / (l_scale * l_scale);
  }

  /**
   * @brief Calculates the scaling factor for moment or torque.
   * @return The derived moment scaling factor.
   */
  constexpr auto MomentScale() const noexcept {
    return ForceScale() * LengthScale();
  }

  /**
   * @brief Calculates the scaling factor for potential (energy per unit mass).
   * @return The derived potential scaling factor.
   */
  constexpr auto PotentialScale() const noexcept {
    return AccelerationScale() * LengthScale();
  }

  /**
   * @brief Calculates the scaling factor for energy.
   * @return The derived energy scaling factor.
   */
  constexpr auto EnergyScale() const noexcept {
    const auto v_scale = VelocityScale();
    return MassScale() * v_scale * v_scale;
  }
  /** @} */

 private:
  /**
   * @brief Provides access to the final derived class instance via CRTP.
   * @return A const reference to the derived class.
   */
  constexpr const auto& Derived() const noexcept {
    return static_cast<const Derived_&>(*this);
  }
};

/**
 * @brief An intermediate helper class for mechanical systems.
 *
 * @details Inherits from `Dimensions` and provides a default `TemperatureScale`
 * of 1.0, simplifying the creation of unit systems where temperature is not a
 * primary variable.
 *
 * @tparam Derived_ The final concrete class that implements the unit system.
 * @tparam Real_ The floating-point type for calculations.
 */
template <typename Derived_, typename Real_ = double>
class MechanicalDimensions : public Dimensions<Derived_, Real_> {
 public:
  /**
   * @brief Provides a default temperature scale of 1.0.
   * @return A scaling factor of 1.0 cast to the appropriate `Real_` type.
   */
  constexpr auto TemperatureScale() const noexcept {
    return static_cast<Real_>(1.0);
  }
};

/**
 * @brief An intermediate helper that allows defining `MassScale` directly.
 *
 * @details Inherits from `MechanicalDimensions` and computes the required
 * `DensityScale` from the `MassScale` and `LengthScale` provided by the final
 * derived class. This is the most user-friendly base for mechanical systems.
 *
 * @tparam Derived_ The final concrete class that implements the unit system.
 * @tparam Real_ The floating-point type for calculations.
 */
template <typename Derived_, typename Real_ = double>
class MechanicalMassDimensions : public MechanicalDimensions<Derived_, Real_> {
 private:
  constexpr const auto& Derived() const noexcept {
    return static_cast<const Derived_&>(*this);
  }

 public:
  /** @brief Retrieves the base length scale from the final derived class. */
  constexpr auto LengthScale() const noexcept {
    return Derived().LengthScale();
  }

  /** @brief Retrieves the base mass scale from the final derived class. */
  constexpr auto MassScale() const noexcept { return Derived().MassScale(); }

  /** @brief Retrieves the base time scale from the final derived class. */
  constexpr auto TimeScale() const noexcept { return Derived().TimeScale(); }

  /**
   * @brief Implements `DensityScale` using `MassScale` and `LengthScale`.
   * @return The computed density scaling factor.
   */
  constexpr auto DensityScale() const noexcept {
    const auto l_scale = Derived().LengthScale();
    return MassScale() / (l_scale * l_scale * l_scale);
  }
};

}  // namespace Dimensions