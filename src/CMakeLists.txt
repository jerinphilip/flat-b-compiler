

find_package(BISON REQUIRED)

BISON_TARGET(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)

find_package(FLEX REQUIRED)
FLEX_TARGET(lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.h
)


ADD_FLEX_BISON_DEPENDENCY(lexer parser)


# llvm_map_components_to_libnames is outdated, so try avoiding it. Adding this
# code to your CMakeList file should fetch all the llvm libraries at configure
# time.

# If you intend to fetch libraries of specific components, just replace all
# with the component names.

# https://stackoverflow.com/a/62939671

execute_process(COMMAND llvm-config --libs all
                OUTPUT_VARIABLE llvm_libraries
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_STRIP_TRAILING_WHITESPACE)

message(STATUS "Bison outputs: ${BISON_parser_OUTPUTS}")
message(STATUS "Flex outputs: ${FLEX_lexer_OUTPUTS}")
add_executable(fb ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS} compiler.cpp interpreter.cpp printer.cpp ast.cpp)
message(STATUS "fb-link-libs: ${FLEX_LIBRARIES} ${llvm_libraries}")
target_link_libraries(fb PRIVATE ${FLEX_LIBRARIES})
target_link_libraries(fb PRIVATE ${llvm_libraries})
target_include_directories(fb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(fb PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(fb PRIVATE -fno-rtti)
# target_include_directories(kaleidoscope PUBLIC ${LLVM_INCLUDE_DIRS})
# target_compile_definitions(kaleidoscope PUBLIC ${LLVM_DEFINITIONS})

# add_executable(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp ${BISON_parser_OUTPUTS})
