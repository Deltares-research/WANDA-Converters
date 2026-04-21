#pragma once
#include "mapping/mapper_base.h"
#include "descriptors/wanda_pipe_descriptor.h"
#include "core/pipe.h"

class WandaPipeToEntityMapper: public pipeline::mapping::MapperBase<WandaPipeDescriptor, Pipe> {
    public:
    WandaPipeToEntityMapper() = default;
    Pipe map(const WandaPipeDescriptor& descriptor) const override;
};


