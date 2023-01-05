SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR RISCV)
# Prevent CMake from testing the toolchain
set(CMAKE_C_COMPILER_FORCED 1)
set(CMAKE_CXX_COMPILER_FORCED 1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

if(MINGW OR CYGWIN OR WIN32)
    set(WHERE_CMD where)
    set(TOOLCHAIN_SUFFIX ".exe")
elseif(UNIX OR APPLE)
    set(WHERE_CMD which)
    set(TOOLCHAIN_SUFFIX "")
endif()

if(${COMPILER} STREQUAL "")
message(FATAL_ERROR "Please specify compiler")
else()
include(${WCHEVT_SDK_BASE}/cmake/${COMPILER}.cmake)
endif()

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH})
# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
