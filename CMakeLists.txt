cmake_minimum_required(VERSION 3.1)

set(target SDOLoggerConsumer)
project(${target} CXX)

find_package(OpenRTM REQUIRED)

include("${PROJECT_SOURCE_DIR}/cmake/utils.cmake")
add_subdirectory(idl)

set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
 add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)



add_definitions(${OPENRTM_CFLAGS})
link_directories(${OPENRTM_LIBRARY_DIRS})

include_directories(${PROJECT_BINARY_DIR}/idl)
 
add_library(${target} SHARED ${target}.cpp ${target}.h SDOLogger.cpp SDOLogger.h LoggerConsumer.cpp LoggerConsumer.h ${ALL_IDL_SRCS})
target_link_libraries(${target} ${OPENRTM_LIBRARIES})
target_include_directories(${target} SYSTEM PRIVATE ${OPENRTM_INCLUDE_DIRS})
add_dependencies(${target} ALL_IDL_TGT)
set_target_properties(${target} PROPERTIES PREFIX "")