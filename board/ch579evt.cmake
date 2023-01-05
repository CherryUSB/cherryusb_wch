set(COMPILER "gcc")
set(USBIP "ch32")
set(CHIP_FAMILY "ch579")
set(TOOLCHAIN_PREFIX arm-none-eabi-)

if(${DEMO_TYPE} STREQUAL "device")
set(USB_DRV "usb_ch58x_dc_usbfs.c")
elseif(${DEMO_TYPE} STREQUAL "host")
set(USB_DRV "usb_hc_usbfs.c")
endif()

sdk_append_source($ENV{WCHEVT_SDK_BASE}/board/startup/startup_ch579_int.c)
sdk_append_source($ENV{WCHEVT_SDK_BASE}/board/startup/startup_ch579.c)
sdk_append_source($ENV{WCHEVT_SDK_BASE}/board/startup/ch579.c)

sdk_add_compile_options(--specs=nano.specs -mthumb -mcpu=cortex-m0 -march=armv6-m -mfloat-abi=soft -g -Os --specs=nosys.specs)
sdk_add_link_options(--specs=nano.specs -mcpu=cortex-m0 -march=armv6-m --specs=nosys.specs -Wl,--no-warn-rwx-segments)

sdk_set_linker_script($ENV{WCHEVT_SDK_BASE}/board/linker/gcc_ch579.ld)