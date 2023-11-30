add_library(PerfectGas
perfectgas/PerfectGasService.cc
perfectgas/PerfectGasService.h
__IEquationOfState.h)

add_library(PerfectGasPAcc
perfectgas/PerfectGasPAccService.cc
perfectgas/PerfectGasPAccService.h
__IEquationOfState.h)

add_library(PerfectGasNAcc
perfectgas/PerfectGasNAccService.cc
perfectgas/PerfectGasNAccService.h
__IEquationOfState.h)

add_library(PerfectGasAccWithSupport
perfectgas/PerfectGasAccWithSupportService.cc
perfectgas/PerfectGasAccWithSupportService.h
__IEquationOfState.h)

add_library(PerfectGasWithSupport
perfectgas/PerfectGasWithSupportService.cc
perfectgas/PerfectGasWithSupportService.h
__IEquationOfState.h)

target_include_directories(PerfectGas PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(PerfectGas PUBLIC Arcane::arcane_core)
target_link_libraries(PerfectGas PRIVATE mahyco_config)

target_include_directories(PerfectGasPAcc PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(PerfectGasPAcc PUBLIC Arcane::arcane_core)
target_link_libraries(PerfectGasPAcc PRIVATE mahyco_config)

target_include_directories(PerfectGasNAcc PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(PerfectGasNAcc PUBLIC Arcane::arcane_core)
target_link_libraries(PerfectGasNAcc PRIVATE mahyco_config)

target_include_directories(PerfectGasAccWithSupport PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(PerfectGasAccWithSupport PUBLIC Arcane::arcane_core)
target_link_libraries(PerfectGasAccWithSupport PRIVATE mahyco_config)

target_include_directories(PerfectGasWithSupport PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(PerfectGasWithSupport PUBLIC Arcane::arcane_core)
target_link_libraries(PerfectGasWithSupport PRIVATE mahyco_config)

if (SCIHOOK_ENABLED)
  target_include_directories(PerfectGas PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(PerfectGas PRIVATE ${SCIHOOK_LIB})

  target_include_directories(PerfectGasPAcc PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(PerfectGasPAcc PRIVATE ${SCIHOOK_LIB})

  target_include_directories(PerfectGasNAcc PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(PerfectGasNAcc PRIVATE ${SCIHOOK_LIB})

  target_include_directories(PerfectGasAccWithSupport PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(PerfectGasAccWithSupport PRIVATE ${SCIHOOK_LIB})

  target_include_directories(PerfectGasWithSupport PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(PerfectGasWithSupport PRIVATE ${SCIHOOK_LIB})
endif()

install(TARGETS PerfectGas EXPORT ${MAHYCO_EXPORT_TARGET})
install(TARGETS PerfectGasPAcc EXPORT ${MAHYCO_EXPORT_TARGET})
install(TARGETS PerfectGasNAcc EXPORT ${MAHYCO_EXPORT_TARGET})
install(TARGETS PerfectGasAccWithSupport EXPORT ${MAHYCO_EXPORT_TARGET})
install(TARGETS PerfectGasWithSupport EXPORT ${MAHYCO_EXPORT_TARGET})

add_library(StiffenedGas
  stiffenedgas/StiffenedGasService.cc
  stiffenedgas/StiffenedGasService.h
  __IEquationOfState.h)

add_library(StiffenedGasAcc
  stiffenedgas/StiffenedGasAccService.cc
  stiffenedgas/StiffenedGasAccService.h
  __IEquationOfState.h)

target_include_directories(StiffenedGas PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(StiffenedGas PUBLIC Arcane::arcane_core)
target_link_libraries(StiffenedGas PRIVATE mahyco_config)

target_include_directories(StiffenedGasAcc PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(StiffenedGasAcc PUBLIC Arcane::arcane_core)
target_link_libraries(StiffenedGasAcc PRIVATE mahyco_config)

if (SCIHOOK_ENABLED)
  target_include_directories(StiffenedGas PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(StiffenedGas PRIVATE ${SCIHOOK_LIB})

  target_include_directories(StiffenedGasAcc PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(StiffenedGasAcc PRIVATE ${SCIHOOK_LIB})
endif()

install(TARGETS StiffenedGas EXPORT ${MAHYCO_EXPORT_TARGET})
install(TARGETS StiffenedGasAcc EXPORT ${MAHYCO_EXPORT_TARGET})

arcane_accelerator_enable()
arcane_accelerator_add_source_files(perfectgas/PerfectGasService.cc)
arcane_accelerator_add_source_files(perfectgas/PerfectGasPAccService.cc)
arcane_accelerator_add_source_files(perfectgas/PerfectGasNAccService.cc)
arcane_accelerator_add_source_files(perfectgas/PerfectGasAccWithSupportService.cc)
arcane_accelerator_add_source_files(perfectgas/PerfectGasWithSupportService.cc)
arcane_accelerator_add_to_target(PerfectGas)
arcane_accelerator_add_to_target(PerfectGasPAcc)
arcane_accelerator_add_to_target(PerfectGasNAcc)
arcane_accelerator_add_to_target(PerfectGasAccWithSupport)
arcane_accelerator_add_to_target(PerfectGasWithSupport)

arcane_accelerator_add_source_files(stiffenedgas/StiffenedGasService.cc)
arcane_accelerator_add_source_files(stiffenedgas/StiffenedGasAccService.cc)
arcane_accelerator_add_to_target(StiffenedGas)
arcane_accelerator_add_to_target(StiffenedGasAcc)

arcane_target_add_axl(PerfectGas perfectgas/PerfectGas)
arcane_target_add_axl(PerfectGasPAcc perfectgas/PerfectGasPAcc)
arcane_target_add_axl(PerfectGasNAcc perfectgas/PerfectGasNAcc)
arcane_target_add_axl(PerfectGasAccWithSupport perfectgas/PerfectGasAccWithSupport)
arcane_target_add_axl(PerfectGasWithSupport perfectgas/PerfectGasWithSupport)

arcane_target_add_axl(StiffenedGas stiffenedgas/StiffenedGas)
arcane_target_add_axl(StiffenedGasAcc stiffenedgas/StiffenedGasAcc)

add_library(eos INTERFACE)
target_link_libraries(eos INTERFACE PerfectGas PerfectGasPAcc PerfectGasNAcc PerfectGasAccWithSupport PerfectGasWithSupport StiffenedGas StiffenedGasAcc)
