cp: cp.o
	g++ -o cp cp.o

cp.o: cp.cpp
	g++ -c cp.cpp

clean:
	rm ./*.o
