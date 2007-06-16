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

HeightmapMatrixCore::HeightmapMatrixCore(const HeightmapCore& hMapCore, int cols, int rows)
{
  this->cols = cols;
  this->rows = rows;
  this->mapWidth = hMapCore.getWidth() / cols;
  this->mapHeight = hMapCore.getHeight() / rows;
  this->mapMargin = hMapCore.getMargin();

  importHeightmapCore(hMapCore);
}

bool HeightmapMatrixCore::importHeightmapCore(const HeightmapCore& hMapCore)
{
  if (getTotalWidth() != hMapCore.getWidth() || getTotalHeight() != hMapCore.getHeight())
    return false;

  for (int i = 0; i < getTotalWidth(); ++i)
    for (int j = 0; j < getTotalHeight(); ++j)
      setPixel(i, j, hMapCore.getPixel(i, j));

  return true;
}

HeightmapCore HeightmapMatrixCore::exportHeightmapCore() 
{
  HeightmapCore hMapCore(getTotalHeight(), getTotalWidth(), getMapMargin());

  for (int i = 0; i < getTotalWidth(); ++i)
    for (int j = 0; j < getTotalHeight(); ++j)
      hMapCore.setPixel(i, j, getPixel(i, j));     

  return hMapCore;
}

double HeightmapMatrixCore::getPixel(int x, int y)
{
	return getElement(x / mapWidth, y / mapHeight).getPixel(x % mapWidth, y % mapHeight);
}

/**
 * @param int x wsporzedna pozioma [0, mapWidth*cols]
 * @param int y wsporzedna pionowa [0, mapHeight*rows]
 * @param double v  
 */
bool HeightmapMatrixCore::setPixel(int x, int y, double v)
{
  if ((x < 0) || (x > getTotalWidth() - 1) || (y < 0) || (y > getTotalHeight() - 1))
		return false; 
  
  getElement(x / mapWidth, y / mapHeight).setPixel(x % mapWidth, y % mapHeight, v);  
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

void HeightmapMatrixCore::clusterFill(double min, double max, short clusterChance, short radius)
{
  HeightmapCore hMapCore = exportHeightmapCore();
  hMapCore.clusterFill(min, max, clusterChance, radius);

  importHeightmapCore(hMapCore);
}

void HeightmapMatrixCore::clusterFilter(short radius)
{
  HeightmapCore hMapCore = exportHeightmapCore();
  hMapCore.clusterFilter(radius);

  importHeightmapCore(hMapCore);
}

void HeightmapMatrixCore::alternateClusterFilter(short radius)
{
  HeightmapCore hMapCore = exportHeightmapCore();
  hMapCore.alternateClusterFilter(radius);

  importHeightmapCore(hMapCore);
}

void HeightmapMatrixCore::liquidFilter(double c, double d, double t, double u, short iters, bool wrap)
{
  HeightmapCore hMapCore = exportHeightmapCore();
  hMapCore.liquidFilter(c, d, t, u, iters, wrap);

  importHeightmapCore(hMapCore);
}

void HeightmapMatrixCore::smoothFilter(short iters, short radius, bool wrap)
{
  HeightmapCore hMapCore = exportHeightmapCore();
  hMapCore.smoothFilter(iters, radius, wrap);

  importHeightmapCore(hMapCore);
}

void HeightmapMatrixCore::terraceFilter(short levels)
{
  HeightmapCore hMapCore = exportHeightmapCore();
  hMapCore.terraceFilter(levels);

  importHeightmapCore(hMapCore);
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

