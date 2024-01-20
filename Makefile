default:
	g++ src/*.cpp -Wall -W -s -pedantic-errors -o build/detailmaker.exe
gdb:
	g++ src/*.cpp -Wall -W -pedantic-errors -o build/detailmaker.exe -ggdb
clang:
	clang++ src/*.cpp -o build/detailmaker.exe -pedantic-errors -W -s
lldb:
	clang++ src/*.cpp -o build/detailmaker.exe -pedantic-errors -W -g
run:
	cd build;./detailmaker.exe;cd ..