include_guard(GLOBAL)

if(NOT AETHERX6100CTRL_USE_FAST_MATH)
  return()
endif()

if(MSVC)
  set(FASTMATH_FLAG "/fp:fast")
else()
  set(FASTMATH_FLAG "-ffast-math")
endif()

check_cxx_compiler_flag(${FASTMATH_FLAG} AETHERX6100CTRL_HAS_FAST_MATH)

if(AETHERX6100CTRL_HAS_FAST_MATH)
  add_compile_options(${FASTMATH_FLAG})
endif()
