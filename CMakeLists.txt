project (simple-svg)
cmake_minimum_required(VERSION 2.8)

add_executable(simple_svg main_1.0.0.cpp simple_svg_1.0.0.hpp)

                     
if(MSVC)
   add_definitions(/D_CRT_SECURE_NO_WARNINGS)
   add_definitions(/D_SCL_SECURE_NO_WARNINGS)
   add_definitions(/DNOMINMAX)
endif(MSVC)
