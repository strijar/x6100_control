add_library(x6100control x6100_control.c x6100_flow.c x6100_gpio.c)
target_include_directories(x6100control PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
