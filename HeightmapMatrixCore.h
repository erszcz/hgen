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

  bool importHeightmapCore(const HeightmapCore& hmapCore);
  HeightmapCore exportHeightmapCore();

	int getCols() const { return cols; }
	int getRows() const { return rows; }
	int getMapWidth() const { return mapWidth; }
	int getMapHeight() const { return mapHeight; }
	int getMapMargin() const { return mapMargin; }
  int getTotalWidth() const { return mapWidth*cols; }
  int getTotalHeight() const { return mapHeight*rows; }
	HeightmapCore & getElement(int xPos, int yPos) { return matrix[yPos][xPos]; }
	double getMax();
	double getMin();

	double getPixel(int x, int y); 
	bool setPixel(int x, int y, double v); 


	void flatFill(double v = 0.0);
	void randomFill(double min = -500., double max = 500.);

	void clusterFill(double min = -500., double max = 500., short clusterChance = 60, short radius = 1);

	void clusterFilter(short radius = 1);
	void alternateClusterFilter(short radius = 1);

	void liquidFilter(double c = 100., double d = 10., double t = .033, double u = 100., short iters = 500, bool wrap = true);

	void smoothFilter(short iters = 250, short radius = 1, bool wrap = true);

	void terraceFilter(short levels);

	void wrapEdges();
	void normalize();
	void joinAll();

	private:
	int cols, rows;
	int mapWidth, mapHeight, mapMargin;
	vector<vector<HeightmapCore> > matrix;
};

#endif
