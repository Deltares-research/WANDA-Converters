add_executable(ModelConversionApp
        main.cpp)

target_link_libraries(ModelConversionApp PRIVATE
        pipeline_conversion
)




add_custom_command(
        TARGET ModelConversionApp
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<$<CONFIG:Debug>:${PROJECT_SOURCE_DIR}/libs/debug>
        $<TARGET_FILE_DIR:ModelConversionApp>
)


