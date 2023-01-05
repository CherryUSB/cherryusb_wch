set(COMPILER "gcc")
set(USBIP "ch32")
set(CHIP_FAMILY "ch58x")
set(TOOLCHAIN_PREFIX riscv-none-embed-)

if(${DEMO_TYPE} STREQUAL "device")
set(USB_DRV "usb_ch58x_dc_usbfs.c")
sdk_append_source($ENV{WCHEVT_SDK_BASE}/board/startup/startup_CH583.S)
sdk_set_linker_script($ENV{WCHEVT_SDK_BASE}/board/linker/ch58x.ld)
elseif(${DEMO_TYPE} STREQUAL "host")
set(USB_DRV "usb_hc_usbfs.c")
sdk_append_source($ENV{WCHEVT_SDK_BASE}/board/startup/startup_CH583_rtt.S)
sdk_set_linker_script($ENV{WCHEVT_SDK_BASE}/board/linker/ch58x_rtt.ld)
sdk_add_compile_definitions(-DDEBUG=1)
sdk_add_compile_definitions(-DCH582)
sdk_add_compile_definitions(-DCONFIG_USBHOST_PIPE_NUM=16)
sdk_add_compile_definitions(-DUSBH_IRQHandler=USB2_IRQHandler)
sdk_add_compile_definitions(-DENABLE_INTERRUPT_NEST=0)
endif()

sdk_add_compile_options(-march=rv32imac -mabi=ilp32 -Wall -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -std=gnu99)
sdk_add_compile_options(-fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g -Os)

sdk_append_source($ENV{WCHEVT_SDK_BASE}/board/startup/ch58x.c)

sdk_add_link_options(-nostartfiles -Xlinker --gc-sections -Wl,--print-memory-usage --specs=nano.specs --specs=nosys.specs)

