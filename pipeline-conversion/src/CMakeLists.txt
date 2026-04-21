add_subdirectory(core)
add_subdirectory(mapping)
add_subdirectory(descriptors)
add_subdirectory(builders)
add_subdirectory(utils)

# Explicit module dependencies

target_link_libraries(pipeline_builders
  PUBLIC
    pipeline_core
    pipeline_descriptors
    pipeline_mapping
)
