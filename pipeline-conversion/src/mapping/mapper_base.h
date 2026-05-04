#pragma once

namespace pipeline::mapping {

/**
 * @brief Abstract base class for mapping (converting) objects from one type to another.
 *
 * @tparam Source The input type to map from.
 * @tparam Target The output type to map to.
 *
 * Methods:
 * - map(source): Converts a Source object into a Target object.
 *   @param source Const reference to the source object.
 *   @return The mapped Target object.
 */
template <typename Source, typename Target>
class MapperBase {
 public:
  virtual ~MapperBase() = default;
  virtual Target map(const Source& source) const = 0;
};

} // namespace pipeline::mapping
