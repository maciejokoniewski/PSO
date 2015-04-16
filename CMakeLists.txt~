# cmake requirements
cmake_minimum_required(VERSION 2.8)

# Build options have to be before PROJECT(...)
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE PATH "Configuration types")
SET(CMAKE_BUILD_TYPE "Release" CACHE PATH "Current build configuration")

# PSO Project configuration
PROJECT(PSO)
SET(CMAKE_CXX_FLAGS "-std=c++0x -pthread")

# Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Settings
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include/Defs")

# core libraries
option(BUILD_PSO "Build PSO libraries" YES)
option(BUILD_PSO "Build PSO" YES)
mark_as_advanced(BUILD_PSO)
option(BUILD_PSO_DEFS "Build PSO Defs library" YES)
mark_as_advanced(BUILD_PSO_DEFS)

# demos
option(BUILD_PSO "Build PSO demonstration programs and libraries" YES)

#additional dependencies
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

#Eigen
add_definitions(-Wno-deprecated -DEIGEN_DONT_VECTORIZE -DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)

# Executable output directory
SET(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Executable output directory")
mark_as_advanced(RUNTIME_OUTPUT_DIRECTORY)

# Dynamic library output directory
SET(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Dynamic library output directory")
mark_as_advanced(LIBRARY_OUTPUT_DIRECTORY)

# Static library output directory
SET(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Static library output directory")
mark_as_advanced(ARCHIVE_OUTPUT_DIRECTORY)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY})
foreach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${CONFIGURATION_TYPE} CONFIGURATION_TYPE)
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${RUNTIME_OUTPUT_DIRECTORY})
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${LIBRARY_OUTPUT_DIRECTORY})
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${ARCHIVE_OUTPUT_DIRECTORY})
endforeach(CONFIGURATION_TYPE CMAKE_CONFIGURATION_TYPES)

if (MSVC)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()


###############################################################################
#
# PSO tinyXML2 library
#
###############################################################################

add_library(tinyxml2 SHARED ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/tinyXML/tinyxml2.h ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/tinyXML/tinyxml2.cpp)

###############################################################################
#
# PSO defs library
#
###############################################################################

if(BUILD_PSO AND BUILD_PSO_DEFS)
        file(GLOB DEFS_HEADERS
            "${CMAKE_SOURCE_DIR}/include/Defs/PSO_defs.h"
        )
        ADD_LIBRARY(PSO_DEFS STATIC ${DEFS_HEADERS})
        set_target_properties(PSO_DEFS PROPERTIES LINKER_LANGUAGE CXX)
# 	INSTALL(TARGETS PUTSLAMDefs RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
        INSTALL(FILES ${DEFS_HEADERS} DESTINATION include/Defs/)

endif(BUILD_PSO AND BUILD_PSO_DEFS)

###############################################################################
#
# PSO library
#
###############################################################################

if(BUILD_PSO)
        file(GLOB LIBPSO_SOURCES
            "${CMAKE_SOURCE_DIR}/src/PSO/*.cpp"
        )
        file(GLOB LIBPSO_HEADERS
            "${CMAKE_SOURCE_DIR}/include/PSO/*.h"
        )
        ADD_LIBRARY(LIBPSO STATIC ${LIBPSO_SOURCES} ${LIBPSO_HEADERS})
        INSTALL(TARGETS LIBPSO RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
        TARGET_LINK_LIBRARIES(LIBPSO tinyxml2)
        INSTALL(FILES ${LIBPUTSLAM_HEADERS} DESTINATION include/pso/PSO/)
endif(BUILD_PSO)

###############################################################################
#
# PSO DEMO executables
#
###############################################################################

if(BUILD_PSO)

        SET(DEMO_SOURCES ./main.cpp)
        ADD_EXECUTABLE(PSO ${DEMO_SOURCES})
        TARGET_LINK_LIBRARIES(PSO tinyxml2)
        INSTALL(TARGETS PSO RUNTIME DESTINATION bin)
        INSTALL(FILES ${DEMO_FILES} DESTINATION bin)

endif(BUILD_PSO)
