if(NOT BUILD_TESTS)
  return()
endif()

add_executable(x6100_atu atu.c)
add_executable(x6100_flow flow.c)
add_executable(x6100_ptt ptt.c)
add_executable(x6100_vfo vfo.c)

target_link_libraries(x6100_atu LINK_PUBLIC x6100control)
target_link_libraries(x6100_flow LINK_PUBLIC x6100control)
target_link_libraries(x6100_ptt LINK_PUBLIC x6100control)
target_link_libraries(x6100_vfo LINK_PUBLIC x6100control)

list(APPEND TO_INSTALL x6100_atu x6100_flow x6100_ptt x6100_vfo)

install(TARGETS ${TO_INSTALL}
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
