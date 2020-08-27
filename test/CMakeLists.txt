add_executable(
    unit_tests
    test_build_treap.cpp
    test_depth.cpp
    test_find.cpp
    test_find_best_fit.cpp
    test_move.cpp
    )

target_include_directories(
	unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include
	)

target_link_libraries(
    unit_tests
    gtest_main
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
