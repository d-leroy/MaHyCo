add_library(RIDER RIDER/RiderService.cc
  RIDER/RiderService.h __IInitialisations.h)
target_include_directories(RIDER PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(RIDER PUBLIC Arcane::arcane_core)
if (SCIHOOK_ENABLED)
  target_include_directories(RIDER PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(RIDER PRIVATE ${SCIHOOK_LIB})
endif()
install(TARGETS RIDER EXPORT ${MAHYCO_EXPORT_TARGET})

add_library(SOD SOD/SodService.cc
  SOD/SodService.h __IInitialisations.h)
target_include_directories(SOD PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(SOD PUBLIC Arcane::arcane_core)
if (SCIHOOK_ENABLED)
  target_include_directories(SOD PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(SOD PRIVATE ${SCIHOOK_LIB})
endif()
install(TARGETS SOD EXPORT ${MAHYCO_EXPORT_TARGET})

add_library(SEDOV SEDOV/SedovService.cc
SEDOV/SedovService.h __IInitialisations.h)
target_include_directories(SEDOV PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(SEDOV PUBLIC Arcane::arcane_core)
if (SCIHOOK_ENABLED)
  target_include_directories(SEDOV PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(SEDOV PRIVATE ${SCIHOOK_LIB})
endif()
install(TARGETS SEDOV EXPORT ${MAHYCO_EXPORT_TARGET})

add_library(OTHER OTHER/OtherService.cc
OTHER/OtherService.h __IInitialisations.h)
target_include_directories(OTHER PRIVATE .. ${CMAKE_BINARY_DIR}/src)
target_link_libraries(OTHER PUBLIC Arcane::arcane_core)
if (SCIHOOK_ENABLED)
  target_include_directories(OTHER PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
  target_link_libraries(OTHER PRIVATE ${SCIHOOK_LIB})
endif()
install(TARGETS OTHER EXPORT ${MAHYCO_EXPORT_TARGET})

arcane_target_add_axl(RIDER RIDER/Rider)
arcane_target_add_axl(SOD SOD/Sod)
arcane_target_add_axl(SEDOV SEDOV/Sedov)
arcane_target_add_axl(OTHER OTHER/Other)

add_library(cas_test INTERFACE)
target_link_libraries(cas_test INTERFACE RIDER SOD SEDOV OTHER)
