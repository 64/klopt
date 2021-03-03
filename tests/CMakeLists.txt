# Testing library
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.4)
FetchContent_MakeAvailable(catch)

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "./*.cpp")
add_executable(test_main ${SOURCE_LIST})
target_compile_features(test_main PRIVATE cxx_std_17)
target_link_libraries(test_main PRIVATE libklopt Catch2::Catch2)

add_test(NAME test_all COMMAND test_main)

