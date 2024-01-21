all := main

main:
	clang++ -std=c++20 -xc++-system-header --precompile iostream -o iostream.pcm
	clang++ -std=c++20 -fmodule-file=iostream.pcm -xc++-module Math.cpp --precompile -o Math.pcm 
	clang++ -std=c++20 main.cpp -fprebuilt-module-path=./ Math.pcm -o main.out

