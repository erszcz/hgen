CXX = g++ -ansi -Wall -pedantic -O2

hmap: HeightmapCore.o libhmap.so

libhmap.so:
	ld -shared -soname libhmap.so.1 -o libhmap.so.1.0 -lc HeightmapCore.o

HeightmapCore.o: ../HeightmapCore.h ../HeightmapCore.cpp
	$(CXX) -fPIC -I../ -c ../HeightmapCore.cpp

clean:
	rm *.o
