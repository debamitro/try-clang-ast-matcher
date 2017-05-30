# try-clang-ast-matcher

A small working example of Clang libtooling which prints out the location of every 'printf' call in a C/C++ source file

How to build
------------
You need to have clang, llvm, llvm-config and development libraries for both clang and llvm.
You do not need to build clang or llvm. Once you have these, doing a make is sufficient

How to run
----------
Generate the pre-processed version of any C/C++ source file you are interested in, by using the -E option (works for both clang and gcc).
Run the executable generated after build like
<path>/test_tool <file-name> -- -c


Inspired by
-----------
https://jonasdevlieghere.com/understanding-the-clang-ast
