#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "nowide::nowide" for configuration "MinSizeRel"
set_property(TARGET nowide::nowide APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(nowide::nowide PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/nowide.lib"
  )

list(APPEND _cmake_import_check_targets nowide::nowide )
list(APPEND _cmake_import_check_files_for_nowide::nowide "${_IMPORT_PREFIX}/lib/nowide.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
