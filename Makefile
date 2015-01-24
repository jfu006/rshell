all: bin rshell cp ls

bin:
		[ ! -d $bin ] && mkdir bin

rshell:
		g++ -Wall -Werror -ansi -pedantic src/main.cpp -o ./bin/rshell
