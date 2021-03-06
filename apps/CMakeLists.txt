add_executable(klopt main.cpp)
target_compile_features(klopt PRIVATE cxx_std_20)
target_link_libraries(klopt PRIVATE libklopt)

pybind11_add_module(kloptpy bindings.cpp)
set_target_properties(libklopt PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(kloptpy PRIVATE libklopt)


