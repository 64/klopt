add_executable(klopt main.cpp)
target_compile_features(klopt PRIVATE cxx_std_20)

target_link_libraries(klopt PRIVATE libklopt)

