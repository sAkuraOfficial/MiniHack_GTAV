cmake_minimum_required(VERSION 3.5)

project(MiniHack_GTAV)

#解决奇数个数中文在msvc上无法编译utf-8不带bom的代码文件
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(external/hello_imgui)
add_subdirectory(module)

hello_imgui_add_app(MiniHack main.cpp MiniHack.cpp MiniHack.h)
target_link_libraries(MiniHack PRIVATE memory)