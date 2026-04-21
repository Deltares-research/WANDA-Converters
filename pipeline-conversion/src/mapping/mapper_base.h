#pragma once

namespace pipeline::mapping {

template <typename Source, typename Target>
class MapperBase {
 public:
  virtual ~MapperBase() = default;
  virtual Target map(const Source& source) const = 0;
};

} // namespace pipeline::mapping
