set(LIB_X6100_SRC_FILES
	x6100_control.c 
	x6100_flow.c 
	x6100_gpio.c
)

if(BUILD_STATIC_LIBS)
	add_library(x6100control_static STATIC ${LIB_X6100_SRC_FILES})
	
	target_include_directories(x6100control_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  	set_target_properties(x6100control_static PROPERTIES OUTPUT_NAME x6100control)
  	
	list(APPEND TO_INSTALL x6100control_static)
endif()

if(BUILD_SHARED_LIBS)
	add_library(x6100control_shared SHARED ${LIB_X6100_SRC_FILES})
	
	target_include_directories(x6100control_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  	set_target_properties(x6100control_shared PROPERTIES OUTPUT_NAME x6100control)
  	
	list(APPEND TO_INSTALL x6100control_shared)
endif()

set(INSTALL_HDRS
  ${CMAKE_CURRENT_SOURCE_DIR}/x6100_control.h
  ${CMAKE_CURRENT_SOURCE_DIR}/x6100_flow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/x6100_gpio.h
)

install(TARGETS ${TO_INSTALL}
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}")

install(FILES ${INSTALL_HDRS}
    DESTINATION "${INSTALL_INC_DIR}/x6100control")
