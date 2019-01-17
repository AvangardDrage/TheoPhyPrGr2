#Makefile to compile multiple executables with the same name as the sources
#https://gist.github.com/juanpabloaj/3726212

FILES = $(basename $(shell ls *cpp))

all: $(FILES)

%: %.cpp
	g++ -o $@ $<

clean:
	rm $(FILES)


