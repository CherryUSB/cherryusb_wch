cmake_minimum_required(VERSION 3.15)
get_filename_component(project_name ${CMAKE_CURRENT_LIST_DIR} NAME)
find_package(plumbl_sdk REQUIRED HINTS $ENV{WCHEVT_SDK_BASE})
sdk_append_inc(.)
sdk_append_inc(..)
sdk_append_source($ENV{WCHEVT_SDK_BASE}/CherryUSB/class/msc/usbd_msc.c)

if(DEBUG)
sdk_add_compile_definitions(-DDEBUG=1)
endif()

sdk_set_main_file(main.c)

project(${BOARD}_usb_${DEMO_TYPE}_${project_name})