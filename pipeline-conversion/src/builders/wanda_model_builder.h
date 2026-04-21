#pragma once

#include <vector>

#include "network.h"
#include "wanda_pipe_descriptor.h"

namespace pipeline::builders {

class WandaModelBuilder {
 public:
  core::Network build(
      const std::vector<descriptors::WandaPipeDescriptor>& descriptors) const;
};

} // namespace pipeline::builders
