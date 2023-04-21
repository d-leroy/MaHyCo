add_library(PerfectGas
perfectgas/PerfectGasService.cc
perfectgas/PerfectGasService.h
__IEquationOfState.h)

target_include_directories(PerfectGas PRIVATE ..)
target_link_libraries(PerfectGas PUBLIC Arcane::arcane_core)
target_link_libraries(PerfectGas PRIVATE mahyco_config)
install(TARGETS PerfectGas EXPORT ${MAHYCO_EXPORT_TARGET})

add_library(StiffenedGas
  stiffenedgas/StiffenedGasService.cc
  stiffenedgas/StiffenedGasService.h
  __IEquationOfState.h)

target_include_directories(StiffenedGas PRIVATE ..)
target_link_libraries(StiffenedGas PUBLIC Arcane::arcane_core)
target_link_libraries(StiffenedGas PRIVATE mahyco_config)
install(TARGETS StiffenedGas EXPORT ${MAHYCO_EXPORT_TARGET})

arcane_accelerator_enable()
arcane_accelerator_add_source_files(perfectgas/PerfectGasService.cc)
arcane_accelerator_add_source_files(stiffenedgas/StiffenedGasService.cc)
arcane_accelerator_add_to_target(PerfectGas)
arcane_accelerator_add_to_target(StiffenedGas)

arcane_target_add_axl(PerfectGas perfectgas/PerfectGas)
arcane_target_add_axl(StiffenedGas stiffenedgas/StiffenedGas)

add_library(eos INTERFACE)
target_link_libraries(eos INTERFACE PerfectGas StiffenedGas)
