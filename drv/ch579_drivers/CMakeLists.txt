sdk_append_inc(${CMAKE_CURRENT_LIST_DIR}/cmsis/inc)
sdk_append_inc(${CMAKE_CURRENT_LIST_DIR}/device/inc)
sdk_append_inc(${CMAKE_CURRENT_LIST_DIR}/driver/inc)

sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_adc.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_clk.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_flash.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_gpio.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_lcd.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_pwm.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_pwr.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_spi0.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_spi1.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_sys.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_timer0.c)
sdk_append_source(${CMAKE_CURRENT_LIST_DIR}/driver/src/CH57x_uart0.c)


