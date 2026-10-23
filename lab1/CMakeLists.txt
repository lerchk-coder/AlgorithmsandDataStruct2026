add_library(lab1_modules)
target_sources(lab1_modules 
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/my_vector.cppm
			${CMAKE_CURRENT_SOURCE_DIR}/std_module/std.ixx
)

add_executable(lab1_app 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(lab1_app PRIVATE lab1_modules)

if(MSVC)
    target_compile_options(lab1_modules PRIVATE /W4 /WX /utf-8)
    target_compile_options(lab1_app PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(lab1_modules PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)
    target_compile_options(lab1_app PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)
endif()