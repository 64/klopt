file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${klopt_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "./*.cpp")

add_library(libklopt ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(libklopt PUBLIC ../include)
target_compile_features(libklopt PUBLIC cxx_std_17)
target_compile_options(libklopt PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
     -Wall -Wextra>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)
