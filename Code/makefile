HPATH = -I ./Headers/ # add for header compilation
EPATH = -I ./Headers/eigenfolder/ # add if matrices are used
CFLAG = -O2

REMOVE_O =  $(shell ls *.o)

solver: main.cpp ObjectInput.cpp Boundary.cpp EigenSor.cpp BDef.cpp GenSolver.cpp AimSolver1.cpp AimSolver2.cpp ASol1.cpp ASol2.cpp SMSD.cpp
	g++ -g $(CFLAG) $(EPATH) $(HPATH) -o $@.exe $^

comparison: Comparison.cpp ObjectInput.cpp Boundary.cpp EigenSor.cpp jac.cpp gauss.cpp BDef.cpp 
	g++ -g $(CFLAG) $(EPATH) $(HPATH) -o $@.exe $^

error1: err_compar1.cpp ObjectInput.cpp Boundary.cpp EigenSor.cpp BDef.cpp ASol1.cpp
	g++ -g $(CFLAG) $(EPATH) $(HPATH) -o $@.exe $^

error2: err_compar2.cpp ObjectInput.cpp Boundary.cpp EigenSor.cpp BDef.cpp ASol2.cpp
	g++ -g $(CFLAG) $(EPATH) $(HPATH) -o $@.exe $^

grid1: grid_err1.cpp ObjectInput.cpp Boundary.cpp EigenSor.cpp BDef.cpp ASol1.cpp
	g++ -g $(CFLAG) $(EPATH) $(HPATH) -o $@.exe $^

grid2: grid_err2.cpp ObjectInput.cpp Boundary.cpp EigenSor.cpp BDef.cpp ASol2.cpp
	g++ -g $(CFLAG) $(EPATH) $(HPATH) -o $@.exe $^

time: time.cpp ObjectInput.cpp Boundary.cpp EigenSor.cpp jac.cpp gauss.cpp BDef.cpp 
	g++ -g $(CFLAG) $(EPATH) $(HPATH) -o $@.exe $^

objclass: Objtest.o ObjectInput.o
	g++ -o $@ $^

Objtest.o: Objtest.cpp ./Headers/ObjectInput.h
	g++ $(HPATH) -c test.cpp

ObjectInput.o: ObjectInput.cpp ./Headers/ObjectInput.h
	 g++ $(HPATH) -c ObjectInput.cpp

laplace_new: laplace_new.o
	g++ -Wall -o $@ $<

laplace_new.o: laplace_new.cpp ./Headers/linspace.h
	g++ $(HPATH) -c laplace.cpp

finite: finite.o
	g++ -Wall -o $@ $<

finite.o: finite.cpp ./Headers/linspace.h
	g++ $(HPATH) -c finite.cpp

meshclass: Meshtest.o MeshSpace.o
	g++ -o $@ $^

Meshtest.o: Meshtest.cpp ./Headers/MeshSpace.h
	g++ $(HPATH) -c Meshtest.cpp

MeshSpace.o: MeshSpace.cpp ./Headers/MeshSpace.h
	g++ $(HPATH) -c Meshtest.cpp

GridGen.o: GridGen.cpp ./Headers/GridGen.h 
	g++ $(HPATH) -c GridGen.cpp

EigenRule: <.cpp> $(EPATH)<include>
	g++ -c <executable> $^

bdtest: bdtest.cpp BDefine.cpp ObjectInput.cpp 
	g++ $(EPATH) $(HPATH) -o $@.exe $^



clean_o: 
	rm $(REMOVE_O)
clean_e:
	rm meshclass finite laplace_new objclass

