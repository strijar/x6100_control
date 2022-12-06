if(NOT AETHERX6100CTRL_BUILD_TEST)
  return()
endif()

add_executable(test_atu test_atu.c)
add_executable(test_flow test_flow.c)
add_executable(test_ptt test_ptt.c)
add_executable(test_vfo test_vfo.c)

target_link_libraries(test_atu LINK_PUBLIC x6100control)
target_link_libraries(test_flow LINK_PUBLIC x6100control)
target_link_libraries(test_ptt LINK_PUBLIC x6100control)
target_link_libraries(test_vfo LINK_PUBLIC x6100control)
