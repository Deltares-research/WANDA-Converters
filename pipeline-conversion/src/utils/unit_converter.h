#pragma once

namespace pipeline::utils {

/**
 * @brief Utility class for converting between measurement units.
 *
 * Provides static methods for unit conversions used throughout the pipeline
 * model.
 *
 * Methods:
 * - meters_to_feet: Converts a length value from meters to feet.
 *   @param meters Length in meters.
 *   @return Length in feet.
 */
class UnitConverter {
  public:
    static double meters_to_feet(double meters);
};

} // namespace pipeline::utils
