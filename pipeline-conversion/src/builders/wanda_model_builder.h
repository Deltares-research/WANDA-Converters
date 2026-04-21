#pragma once

#include <vector>

#include "../core/network.h"
#include "../descriptors/wanda_pipe_descriptor.h"

namespace pipeline::builders {

class WandaModelBuilder {
 public:
  core::Network build(
      const std::vector<descriptors::WandaPipeDescriptor>& descriptors) const;
};

} // namespace pipeline::builders
