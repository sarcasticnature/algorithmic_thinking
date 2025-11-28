add_executable(homer homer.c)
add_executable(homer_dp homer_dp.c)
configure_file(homer_input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(homer_output.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_test(
  NAME test_homer
  COMMAND ${CMAKE_BINARY_DIR}/test.sh $<TARGET_FILE:homer> homer_input.txt homer_output.txt 3
)

add_test(
  NAME test_homer_dp
  COMMAND ${CMAKE_BINARY_DIR}/test.sh $<TARGET_FILE:homer_dp> homer_input.txt homer_output.txt 3
)

add_executable(moneygrubbers moneygrubbers.c)
add_executable(moneygrubbers_memo moneygrubbers_memo.c)
configure_file(moneygrubbers_input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(moneygrubbers_output.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_test(
  NAME test_moneygrubbers
  COMMAND ${CMAKE_BINARY_DIR}/test.sh $<TARGET_FILE:moneygrubbers> moneygrubbers_input.txt moneygrubbers_output.txt 3
)

add_test(
  NAME test_moneygrubbers_memo
  COMMAND ${CMAKE_BINARY_DIR}/test.sh $<TARGET_FILE:moneygrubbers_memo> moneygrubbers_input.txt moneygrubbers_output.txt 3
)
