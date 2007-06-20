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
	double getPixel(int x, int y) const;
	double getMax() const;
	double getMin() const;

	bool setPixel(int x, int y, double value);

	void flatFill(double v = 0.0);
	void randomFill(double min = -500., double max = 500.);

	void clusterFill(double min = -500., double max = 500.,
	                 short clusterChance = 60, short radius = 1);

	void clusterFilter(int radius = 1);

	void alternateClusterFilter(short radius = 0);

	void liquidFilter(double c = 100., double d = 10., double t = .033, double u = 100., bool wrap = true);

	void smoothFilter(short radius = 1, bool wrap = true);
	void terraceFilter(short levels);

	void walkerFilter(int incStep, int decStep, bool wrap);

	void faultingFilter(int incStep, int decStep, bool wrap);

	void wrapEdges();

	void normalize();
	void normalize(double max, double min);

	void join(HeightmapCore & neighbour, Direction edge);

  bool hasMask();

	// funkcja tymczasowa. na dluzsza mete trzeba bedzie overloadnac << dla plikow i, byc moze, dla konsoli
	void print(double val) const
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
	double _random(double min, double max) const;
	bool _isValidPixel(int x, int y) const;
	
	int height, realHeight;
	int width, realWidth;
	int margin;
  vector<vector<double> > map;
  vector<vector<double> > mask;
};

#endif
