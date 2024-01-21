all := main

main:
	clang++ -std=c++20 -xc++-system-header --precompile iostream -o iostream.pcm
	clang++ -std=c++20 -x c++-module -fmodule-file=iostream.pcm Math.c++ --precompile -o Math.pcm 
	clang++ -std=c++20 main.c++ -fmodule-file=iostream.pcm -fprebuilt-module-path=./ Math.pcm -o main.out

