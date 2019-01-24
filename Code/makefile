INC = -I ./Headers/ # add for header compilation

REMOVE_O =  $(shell ls *.o)

objclass: Objtest.o ObjectInput.o
	g++ -o $@ $^

Objtest.o: Objtest.cpp ./Headers/ObjectInput.h
	g++ $(INC) -c test.cpp

ObjectInput.o: ObjectInput.cpp ./Headers/ObjectInput.h
	 g++ $(INC) -c ObjectInput.cpp

laplace_new: laplace_new.o
	g++ -Wall -o $@ $<

laplace_new.o: laplace_new.cpp ./Headers/linspace.h
	g++ $(INC) -c laplace.cpp

finite: finite.o
	g++ -Wall -o $@ $<

finite.o: finite.cpp ./Headers/linspace.h
	g++ $(INC) -c finite.cpp

meshclass: Meshtest.o MeshSpace.o
	g++ -o $@ $^

Meshtest.o: Meshtest.cpp ./Headers/MeshSpace.h
	g++ $(INC) -c Meshtest.cpp

MeshSpace.o: MeshSpace.cpp ./Headers/MeshSpace.h
	g++ $(INC) -c Meshtest.cpp

GridGen.o: GridGen.cpp ./Headers/GridGen.h 
	g++ $(INC) -c GridGen.cpp


clean_o: 
	rm $(REMOVE_O)
clean_e:
	rm meshclass finite laplace_new objclass




# test.o ObjectInput.o laplace_new.o finite.o meshclass Meshtest.o MeshSpace.o GridGen.o
