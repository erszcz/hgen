#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "HeightmapMatrixCore.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;
using std::max_element;
using std::min_element;
using std::copy;

HeightmapMatrixCore::HeightmapMatrixCore(int cols, int rows, int mapWidth, int mapHeight, int mapMargin)
{
	// inicjalizacja atrybutow obiektu
	this->cols = cols;
	this->rows = rows;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->mapMargin = mapMargin;

	// inicjalizacja mapy
	HeightmapCore tmpMap(mapHeight, mapWidth, mapMargin);
	vector<HeightmapCore> tmpRow(cols, tmpMap);
	matrix = vector<vector<HeightmapCore> >(rows, tmpRow);
}

HeightmapMatrixCore::HeightmapMatrixCore(const HeightmapMatrixCore& old)
{
	cols = old.cols;
	rows = old.rows;
	mapWidth = old.mapWidth;
	mapHeight = old.mapHeight;
	mapMargin = old.mapMargin;
	
	matrix = vector<vector<HeightmapCore> >(old.matrix);
}

HeightmapMatrixCore::HeightmapMatrixCore(const HeightmapCore& hMap, int cols, int rows)
{
 /* cols = 
  mapDim = hMap.getWidth() / cols > hMap.getHeight() / rows ?
  */
}

double HeightmapMatrixCore::getPixel(int x, int y)
{
	return getElement(x / mapWidth, y / mapHeight).getPixel(x % mapWidth, y % mapHeight);
}

double HeightmapMatrixCore::getMax()
{
	double max = getElement(0, 0).getMax();
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++) {
			double tmpMax = getElement(i, j).getMax();
			if (tmpMax > max)
				max = tmpMax;
		}
		
	return max;	
}

double HeightmapMatrixCore::getMin()
{
	double min = getElement(0, 0).getMin();
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++) {
			double tmpMin = getElement(i, j).getMin();
			if (tmpMin < min)
				min = tmpMin;
		}
		
	return min;	
}

void HeightmapMatrixCore::flatFill(double v)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j].flatFill(v);
}

void HeightmapMatrixCore::randomFill(double min, double max)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j].randomFill(min, max);
}

void HeightmapMatrixCore::wrapEdges() {
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			getElement(i, j).wrapEdges();
}

void HeightmapMatrixCore::normalize()
{
	double max = getMax();
	double min = getMin();
	
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			getElement(i, j).normalize(max, min);
}

void HeightmapMatrixCore::joinAll()
{
	for (int i = 0; i < cols - 1; i++)
		for (int j = 0; j < rows; j++)
			getElement(i, j).join(getElement(i + 1, j), HE_S);
	
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows - 1; j++)
			getElement(i, j).join(getElement(i, j + 1), HE_E);
}

