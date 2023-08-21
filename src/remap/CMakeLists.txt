add_library(Remap
    adi/RemapADIService.cc
    adi/RemapADIUtils.cc
    adi/RemapADIDualPhaseRemap.cc
    adi/RemapADIRemapVariables.cc
    adi/RemapADI.axl
    # ale/RemapALEService.cc
    # ale/RemapALE.axl
)

target_include_directories(Remap PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(Remap PUBLIC Arcane::arcane_core)
target_link_libraries(Remap PRIVATE mahyco_config)
if (SCIHOOK_ENABLED)
  target_include_directories(Remap PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(Remap PRIVATE ${SCIHOOK_LIB})
endif()
install(TARGETS Remap EXPORT ${MAHYCO_EXPORT_TARGET})

arcane_accelerator_enable()
arcane_accelerator_add_source_files(adi/RemapADIService.cc)
# arcane_accelerator_add_source_files(ale/RemapALEService.cc)
arcane_accelerator_add_to_target(Remap)

arcane_target_add_axl(Remap adi/RemapADI)
# arcane_target_add_axl(Remap ale/RemapALE)
