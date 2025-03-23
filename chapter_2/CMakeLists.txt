add_executable(halloween halloween.c)
configure_file(halloween_input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(halloween_output.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_test(
  NAME test_halloween
  COMMAND ${CMAKE_BINARY_DIR}/test.sh $<TARGET_FILE:halloween> halloween_input.txt halloween_output.txt 2
)
