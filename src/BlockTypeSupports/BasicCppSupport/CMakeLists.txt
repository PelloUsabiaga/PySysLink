# Define a library
add_library(BasicCppSupport STATIC
    SampleTimeConversion.cpp
    SimulationBlockCpp.cpp
    BlockFactoryCpp.cpp
)

target_include_directories(BasicCppSupport PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(BasicCppSupport PRIVATE PySysLinkBase)
target_link_libraries(BasicCppSupport PRIVATE BasicCpp)
target_link_libraries(BasicCppSupport PRIVATE BasicBlocks)

# Include directories for header files
target_include_directories(BasicCppSupport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})