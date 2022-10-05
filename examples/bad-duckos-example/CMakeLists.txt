set(DUCK_SRCS
    main.cpp
    )

add_executable(qt1Test ${DUCK_SRCS})
target_link_libraries(qt1Test PRIVATE Qt::Qt1)
install(TARGETS qt1Test RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
