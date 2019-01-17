INC = -I ./Headers/ # add for header compilation

REMOVE = $(basename $(shell ls *.o)).o

objclass: test.o ObjectInput.o
	g++ -o $@ $^

test.o: test.cpp ./Headers/ObjectInput.h
	g++ $(INC) -c test.cpp

ObjectInput.o: ObjectInput.cpp ./Headers/ObjectInput.h
	 g++ $(INC) -c ObjectInput.cpp

laplace_new: laplace_new.o
	g++ -Wall -o $@ $<

laplace_new.o: laplace_new.cpp ./Headers/linspace.h
	g++ $(INC) -c laplace.cpp

finite: finite.o
	g++ -Wall -o $@ $<

finite.o: finite.cpp
	g++ $(INC) -c finite.cpp

clean: 
	rm test.o ObjectInput.o laplace_new.o finite.o objclass laplace_new finite
