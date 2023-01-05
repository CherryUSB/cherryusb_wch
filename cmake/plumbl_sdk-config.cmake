if(NOT DEFINED ENV{WCHEVT_SDK_BASE})
    message( "please set WCHEVT_SDK_BASE in your system environment")
endif()

set(WCHEVT_SDK_BASE $ENV{WCHEVT_SDK_BASE})

set(build_dir ${CMAKE_CURRENT_BINARY_DIR}/build_out)
set(PROJECT_SOURCE_DIR ${WCHEVT_SDK_BASE})
set(PROJECT_BINARY_DIR ${build_dir})
set(EXECUTABLE_OUTPUT_PATH ${build_dir})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set_property(GLOBAL APPEND PROPERTY SOURCE_LIST)
set_property(GLOBAL APPEND PROPERTY INCLUDE_LIST)

add_library(sdk_intf_lib INTERFACE)

include(${WCHEVT_SDK_BASE}/cmake/showlog.cmake)
include(${WCHEVT_SDK_BASE}/cmake/extension.cmake)
include(${WCHEVT_SDK_BASE}/board/${BOARD}.cmake)
include(${WCHEVT_SDK_BASE}/cmake/toolchain.cmake)

enable_language(C CXX ASM)

add_subdirectory(${WCHEVT_SDK_BASE} ${build_dir})