add_executable(ModelConversionApp
        main.cpp)

target_link_libraries(ModelConversionApp PRIVATE
        pipeline_conversion
)