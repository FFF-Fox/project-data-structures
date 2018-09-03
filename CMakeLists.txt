cmake_minimum_required (VERSION 2.6)
project (TrieMain)

include_directories(include)

add_executable (TrieMain
    src/trie_main.cpp
    include/Trie.cpp
    )
