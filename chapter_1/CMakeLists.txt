add_executable(login login.c)
configure_file(login_input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(login_output.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_test(
  NAME test_login
  COMMAND ${CMAKE_BINARY_DIR}/test.sh $<TARGET_FILE:login> login_input.txt login_output.txt 3
)
