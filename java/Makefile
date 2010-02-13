CXX = g++ -ansi -Wall -pedantic -O2
INCLUDE = -I /usr/lib/jvm/java-6-openjdk/include/

hmap: libhmap.so
#	ln -s libhmap.so.1.0 libhmap.so; \
#	ln -s libhmap.so.1.0 libhmap.so.1

#libhmap.so:
#	ld -shared -soname libhmap.so.1 -o libhmap.so.1.0 -lc CHeightmap.o
# Linking with ld leads to __dso_handle symbol not found in resulting library.
# Java loader complains about it missing.

libhmap.so: CHeightmap.o
	g++ -shared -o libhmap.so CHeightmap.o

CHeightmap.o: CHeightmap.h CHeightmap.cpp
	$(CXX) $(INCLUDE) -fPIC -I../ -c CHeightmap.cpp

clean:
	rm *.o

clean-all:
	rm *.o libhmap.so
#	rm *.o libhmap.so libhmap.so.1 libhmap.so.1.0
