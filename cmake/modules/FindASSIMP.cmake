# - Try to find Assimp
# Once done, this will define
#
# ASSIMP_FOUND - system has Assimp
# ASSIMP_INCLUDE_DIR - the Assimp include directories
# ASSIMP_LIBRARIES - link these to use Assimp
FIND_PATH( ASSIMP_INCLUDE_DIR assimp/mesh.h
        ${CMAKE_SOURCE_DIR}/dependencies/assimp/include
        /usr/include
        /usr/local/include
        /opt/local/include
        ${CMAKE_SOURCE_DIR}/includes
        )
FIND_LIBRARY( ASSIMP_LIBRARY assimp
        ${CMAKE_SOURCE_DIR}/dependencies/assimp/lib
        /usr/lib64
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        ${CMAKE_SOURCE_DIR}/lib
        )
SET(ASSIMP_DLL ${CMAKE_SOURCE_DIR}/dependencies/assimp/bin/assimp-vc142-mtd.dll)
IF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY AND ASSIMP_DLL)
    SET( ASSIMP_FOUND TRUE )
    SET( ASSIMP_LIBRARIES ${ASSIMP_LIBRARY} )
ENDIF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY AND ASSIMP_DLL)
IF(ASSIMP_FOUND)
    IF(NOT ASSIMP_FIND_QUIETLY)
        MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
    ENDIF(NOT ASSIMP_FIND_QUIETLY)
ELSE(ASSIMP_FOUND)
    IF(ASSIMP_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find libASSIMP")
    ENDIF(ASSIMP_FIND_REQUIRED)
ENDIF(ASSIMP_FOUND)