cmake_minimum_required (VERSION 3.8)
project (data-structures)

add_library (Trie src/Trie/Trie.cpp)
target_include_directories (Trie
PUBLIC
    $<INSTALL_INTERFACE:include/Trie>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Trie>
PRIVATE
    $<${CMAKE_CURRENT_SOURCE_DIR}/src/Trie
)

add_executable (
    main
    src/trie_main.cpp)


target_link_libraries (main
    Trie)