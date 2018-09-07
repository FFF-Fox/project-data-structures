cmake_minimum_required (VERSION 3.8)
project (data-structures)

add_library (Alg src/Alg/alg.cpp)
target_include_directories (Alg
PUBLIC
    $<INSTALL_INTERFACE:include/Alg>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Alg>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/alg.cpp
)

add_library (CLI src/CLI/Cli.cpp)
target_include_directories (CLI
PUBLIC
    $<INSTALL_INTERFACE:include/CLI>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/CLI>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Cli.cpp
)

add_executable (
    search_main
    src/search_main.cpp
)

target_link_libraries (search_main
    Alg
    CLI
)

add_library (Trie src/Trie/Trie.cpp)
target_include_directories (Trie
PUBLIC
    $<INSTALL_INTERFACE:include/Trie>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Trie>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Trie
)

add_executable (
    trie_main
    src/trie_main.cpp
)

target_link_libraries (trie_main
    Trie
    CLI
)