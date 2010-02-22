#ifndef HEIGHTMAPCORE_H
#define HEIGHTMAPCORE_H

#include <vector>
using std::vector;

// temporary
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
// koniec

typedef enum {HE_N, HE_E, HE_S, HE_W} Direction;


class HeightmapCore {
	public:
	HeightmapCore(int height, int width, int margin = 1);
	HeightmapCore(const HeightmapCore& old);
	~HeightmapCore() {;}

	int getHeight() const { return height; }
	int getWidth() const { return width; }
	int getMargin() const { return margin; }
	float getPixel(int x, int y) const;
	float getMax();
	float getMin();

	bool setPixel(int x, int y, float value);

	void flatFill(float v = 0.0);
	void randomFill(float min = -500., float max = 500.);

	void clusterFill(float min = -500., float max = 500.,
	                 int clusterChance = 60, int radius = 1);

	void clusterFilter(int radius = 1);

	void alternateClusterFilter(int radius = 0);

	void liquidFilter(float c = 100., float d = 10., float t = .033, float u = 100., bool wrap = true);

	void smoothFilter(int radius = 1, bool wrap = true);
	void terraceFilter(int levels);

	void walkerFilter(int incStep, int decStep, bool wrap);

	void faultingFilter(int incStep, int decStep, bool wrap);

	void wrapEdges();

	void normalize();
	void normalize(float max, float min);

	void join(HeightmapCore & neighbour, Direction edge);

  bool hasMask() const;

	// temp
	void print(float val) const
	{
		cout.width(3);
		cout << val;
	}
	void tempPrint() const {
		cout << setw(12) << std::left << "Row:" << std::right;
		for (int l = 0; l < realWidth; ++l)
			print(l);
		cout << endl << "------------";
		for (int l = 0; l < realWidth; ++l)
			cout << "---";
		cout << endl;
		for (int i = 0; i < realHeight; ++i) {
			cout << "Line:" << setw(4) << i << " | ";
			for (int j = 0; j < realWidth; ++j)
				print(map[i][j]);
			cout << endl;
		}
	}
	// fin

	private:
	float _random(float min, float max) const;
	bool _isValidPixel(int x, int y) const;
  void _minmax(); // calculate cachedMin and cachedMax and set dirty to false
    // as long as dirty stays false cached values are valid
	
	int height, realHeight;
	int width, realWidth;
	int margin;
  vector<vector<float> > map;
  vector<vector<float> > mask;

  float cachedMin, cachedMax;
  bool dirty;
};

#endif
