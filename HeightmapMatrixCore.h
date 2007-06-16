#ifndef HEIGHTMAPMATRIXCORE_H
#define HEIGHTMAPMATRIXCORE_H

#include <vector>
using std::vector;

#include "HeightmapCore.h"


// temporary
#include <iostream>
using std::cout;
using std::endl;
// koniec

class HeightmapMatrixCore {
	public:
	HeightmapMatrixCore(int cols, int rows, int mapWidth, int mapHeight, int mapMargin = 1);
	HeightmapMatrixCore(const HeightmapMatrixCore& old);
  HeightmapMatrixCore(const HeightmapCore& hMap, int cols, int rows);
	~HeightmapMatrixCore() {;}

	int getCols() const { return cols; }
	int getRows() const { return rows; }
	int getMapWidth() const { return mapWidth; }
	int getMapHeight() const { return mapHeight; }
	int getMapMargin() const { return mapMargin; }
	HeightmapCore & getElement(int xPos, int yPos) { return matrix[yPos][xPos]; }
	double getPixel(int x, int y); 
	double getMax();
	double getMin();


	void flatFill(double v = 0.0);
	void randomFill(double min = -500., double max = 500.);

/*	void clusterFill(double min = -500., double max = 500.,
	                 short clusterChance = 60, short radius = 1);

	void clusterFilter(short radius = 1);

	void liquidFilter(double c = 100., double d = 10., double t = .033,
	                  double u = 100., short iters = 500, bool wrap = true);

	void smoothFilter(short iters = 250, short radius = 1, bool wrap = true);

	void wrapEdges();
*/
	void wrapEdges();
	void normalize();
	void joinAll();

	private:
	int cols, rows;
	int mapWidth, mapHeight, mapMargin;
	vector<vector<HeightmapCore> > matrix;
};

#endif
