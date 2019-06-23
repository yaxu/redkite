#set(RK_TOOLS_SOURCES ${RK_TOOLS_PATH}/rkpng2c.c)
set(RK_TOOLS_SOURCES rkpng2c.c)
add_executable(rkpng2c ${RK_EXEC_OPTION} ${RK_TOOLS_SOURCES})

if (CMAKE_SYSTEM_NAME MATCHES Windows)
  target_link_libraries(rkpng2c "-mwindows -lcairo -lm")
else()
   target_link_libraries(rkpng2c "-lcairo")
endif()

install(TARGETS rkpng2c DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
