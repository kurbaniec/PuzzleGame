# - Try to find SOIL2
# Once done, this will define
#
# SOIL2_FOUND - system has SOIL2
# SOIL2_INCLUDE_DIR - the SOIL2 include directories
# SOIL2_LIBRARIES - link these to use SOIL2
FIND_PATH( SOIL2_INCLUDE_DIR SOIL2.h
        ${CMAKE_SOURCE_DIR}/dependencies/SOIL2/include
        )
FIND_LIBRARY( SOIL2_LIBRARY soil2.lib
        ${CMAKE_SOURCE_DIR}/dependencies/SOIL2/lib
        )
IF(SOIL2_INCLUDE_DIR AND SOIL2_LIBRARY)
    SET( SOIL2_FOUND TRUE )
    SET( SOIL2_LIBRARIES ${SOIL2_LIBRARY} )
ENDIF(SOIL2_INCLUDE_DIR AND SOIL2_LIBRARY)
IF(SOIL2_FOUND)
    IF(NOT SOIL2_FIND_QUIETLY)
        MESSAGE(STATUS "Found SOIL2: ${SOIL2_LIBRARY}")
    ENDIF(NOT SOIL2_FIND_QUIETLY)
ELSE(SOIL2_FOUND)
    IF(SOIL2_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find libSOIL2")
    ENDIF(SOIL2_FIND_REQUIRED)
ENDIF(SOIL2_FOUND)