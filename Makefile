cp: cp.o
	g++ --std=c++11 -o cp cp.o

cp.o: cp.cpp
	g++ --std=c++11 -c cp.cpp

clean:
	rm -f ./*.o
