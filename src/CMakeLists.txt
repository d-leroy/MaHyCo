# set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -pedantic -Wnon-virtual-dtor -g " CACHE STRING "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_library(mahyco_config INTERFACE)
if (WANT_PROF_ACC)
    target_compile_definitions(mahyco_config INTERFACE PROF_ACC)
endif ()
# Pour avoir des #warning explicites
target_compile_definitions(mahyco_config INTERFACE P4GPU_HAS_WARNING_INFO)

find_package(Arcane)
# Indique la version minimale de Arcane nécessaire
# À partir de la version 3.8 de Arcane, il sera possible
# d'utiliser directement 'find_package(Arcane 3.8 REQUIRED)'
if (Arcane_VERSION VERSION_LESS "3.6")
  message(FATAL_ERROR "Arcane version '${Arcane_VERSION}' is too old."
    " Version 3.6+ is required")
endif()

# Python embedding
configure_file(scihookdefs.h.in ${CMAKE_BINARY_DIR}/src/scihook/scihookdefs.h)
if (SCIHOOK_ENABLED)
    list(APPEND CMAKE_PREFIX_PATH "${SCIHOOK_INSTALL_PREFIX}")
    set(pybind11_DIR "${Python_SITELIB}/pybind11/share/cmake/pybind11")
    find_package(pybind11 REQUIRED)

    find_library(SCIHOOK_LIB scihook)
endif()

if (WANT_CUDA AND NOT ARCANE_HAS_CUDA)
    MESSAGE(FATAL_ERROR "WANT_CUDA enabled but Arcane was compiled without CUDA support.")
endif()

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(MAHYCO_EXPORT_TARGET ${PROJECT_NAME}Targets)

add_executable(Mahyco
        mahyco/MahycoAnnexe.cc
        MahycoConfig.cmake.in
        mahyco/MahycoModule.cc
        mahyco/MahycoModule.h
        main.cc)

arcane_add_arcane_libraries_to_target(Mahyco)
arcane_target_add_axl(Mahyco mahyco/Mahyco)
target_include_directories(Mahyco PRIVATE . ${CMAKE_CURRENT_BINARY_DIR})
if (SCIHOOK_ENABLED)
  target_include_directories(Mahyco PUBLIC ${SCIHOOK_INSTALL_PREFIX}/include ${pybind11_INCLUDE_DIRS})
endif()


install(TARGETS Mahyco EXPORT ${MAHYCO_EXPORT_TARGET})
configure_file(Mahyco.config ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
install(FILES Mahyco.config DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(cas_test)

# Equation of State
add_subdirectory(eos)

# Remap
add_subdirectory(remap)

# Cartesian
add_subdirectory(cartesian)

# Services communs pour les accélérateurs
add_subdirectory(accenv)

# Message Passing
add_subdirectory(msgpass)

# Pour la gestion des accélérateurs et des sources à compiler avec le
# compilateur pour accélérateur
arcane_accelerator_enable()
arcane_accelerator_add_source_files(mahyco/MahycoModule.cc)
arcane_accelerator_add_source_files(mahyco/MahycoAnnexe.cc)
arcane_accelerator_add_to_target(Mahyco)

target_link_libraries(Mahyco PRIVATE mahyco_config cas_test Remap cartesian eos accenv msgpass)
if (SCIHOOK_ENABLED)
  target_link_libraries(Mahyco PRIVATE ${SCIHOOK_LIB} pybind11::embed)
endif()

# Configuration
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(namespace "Alien::")

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
        "${version_config}" COMPATIBILITY SameMajorVersion
)

set(MAHYCO_MODULE_PATH "${config_install_dir}")

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
        "MahycoConfig.cmake.in"
        "${project_config}"
        INSTALL_DESTINATION "${config_install_dir}"
        PATH_VARS MAHYCO_MODULE_PATH
)

set(Mahyco_project_config "${project_config}" CACHE FILEPATH "Mahyco project config" FORCE)
get_filename_component(Mahyco_config_build_dir "${project_config}" DIRECTORY CACHE)
set(Mahyco_config_install_dir "${config_install_dir}" CACHE STRING "Mahyco config install dir" FORCE)
set(Mahyco_VERSION "${Mahyco_VERSION}" CACHE STRING "Mahyco version" FORCE)

install(FILES "${project_config}" "${version_config}"
        DESTINATION "${config_install_dir}"
        )

install(EXPORT ${MAHYCO_EXPORT_TARGET}
        NAMESPACE ${namespace}
        DESTINATION ${config_install_dir})
