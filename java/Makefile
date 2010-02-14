CXX = g++ -ansi -Wall -pedantic -O2 -fPIC -c 
INCLUDE = -I ../ -I /usr/lib/jvm/java-6-openjdk/include/
DIST = dist

hmap: libhmap.so
#	ln -s libhmap.so.1.0 libhmap.so; \
#	ln -s libhmap.so.1.0 libhmap.so.1

#libhmap.so:
#	ld -shared -soname libhmap.so.1 -o libhmap.so.1.0 -lc CHeightmap.o
# Linking with ld leads to __dso_handle symbol not found in resulting library.
# Java loader complains about it missing.

libhmap.so: HeightmapCore.o lavrin_hgen_CHeightmap.o
	g++ -shared -o libhmap.so HeightmapCore.o lavrin_hgen_CHeightmap.o

lavrin_hgen_CHeightmap.o: lavrin_hgen_CHeightmap.h lavrin_hgen_CHeightmap.cpp
	$(CXX) $(INCLUDE) lavrin_hgen_CHeightmap.cpp

HeightmapCore.o: ../HeightmapCore.h ../HeightmapCore.cpp
	$(CXX) $(INCLUDE) ../HeightmapCore.cpp

clean:
	rm *.o

clean-all: clean
	rm libhmap.so
#	rm $(DIST)/lib/libhmap.so
#	rm *.o libhmap.so libhmap.so.1 libhmap.so.1.0
