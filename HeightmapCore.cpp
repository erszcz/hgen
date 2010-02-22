#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "HeightmapCore.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;
using std::max_element;
using std::min_element;
using std::copy;

HeightmapCore::HeightmapCore(int height, int width, int margin)
{
	srand(time(0));

	// inicjalizacja atrybutow obiektu
	this->height = height;
	realHeight = height + 2*margin;
	this->width = width;
	realWidth = width + 2*margin;
	this->margin = margin;

	this->dirty = true;
	this->cachedMin = 0;
	this->cachedMax = 0;

	// inicjalizacja mapy
	//vector<float> tmp(realWidth, 0.);
	//map = vector<vector<float> >(realHeight, tmp);
  map = vector<vector<float> >(realHeight, vector<float>(realWidth, 0.));

	// inicjalizacja maski (test)
	//vector<float> tmpm(width, 0.);
	//mask = vector<vector<float> >(height, tmpm);
  mask = vector<vector<float> >(height, vector<float>(width, 0.));

  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j)
  //    mask[i][j] = j/(float)width;
      mask[i][j] = 1;
}

HeightmapCore::HeightmapCore(const HeightmapCore& old)
{
	/* mozna tak, jesli mamy gettery
	margin = old.getMargin();
	height = old.getHeight();
	realHeight = height + 2*margin;
	width = old.getWidth();
	realWidth = width + 2*margin; */
	this->height = old.height;
	this->realHeight = old.realHeight;
	this->width = old.width;
	this->realWidth = old.realWidth;
	this->margin = old.margin;

	this->dirty = old.dirty;
	this->cachedMin = old.cachedMin;
	this->cachedMax = old.cachedMax;

	map = vector<vector<float> >(old.map);
  mask = vector<vector<float> >(old.mask);
}

float HeightmapCore::getPixel(int x, int y) const
{
	return map[margin + y][margin + x];
}

bool HeightmapCore::setPixel(int x, int y, float value)
{
  dirty = true;

	if ((x > width - 1) || (y > height -1))
		return false;

	map[y + margin][x + margin] = value;
	return true;
}

void HeightmapCore::flatFill(float v)
{
  dirty = true;

  if (hasMask()) 
  {
    for (int i = margin; i < margin + height; ++i)
      for (int j = margin; j < margin + width; ++j)
        map[i][j] = mask[i - margin][j - margin]*v;
  }
  else
  {
    for (int i = margin; i < margin + height; ++i)
      for (int j = margin; j < margin + width; ++j)
        map[i][j] = v;
  }
}

void HeightmapCore::randomFill(float min, float max)
{
  dirty = true;

  if (hasMask()) 
  {
    for (int i = margin; i <= realHeight - (margin + 1); ++i)
      for (int j = margin; j <= realWidth - (margin + 1); ++j)
        map[i][j] = map[i][j] + _random(min, max)*mask[i - margin][j - margin];
  }
  else
  {
    for (int i = margin; i <= realHeight - (margin + 1); ++i)
      for (int j = margin; j <= realWidth - (margin + 1); ++j)
        map[i][j] = map[i][j] + _random(min, max);
  }
}

void HeightmapCore::clusterFill(float min, float max, int clusterChance, int radius)
{
  dirty = true;

	if (radius > margin)
		radius = margin;

  vector<int> sequence;
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
      sequence.push_back(j + i*width);

  random_shuffle(sequence.begin(), sequence.end());

  vector<int>::iterator it = sequence.begin();  
  while (it != sequence.end()) {
    int i = (*it)/width + margin;
    int j = (*it)%width + margin;

    if (hasMask()) 
    {
      if (_random(0, 100) > clusterChance)
        map[i][j] = map[i][j] + _random(min, max)*mask[i - margin][j - margin];
      else if ( fabs(map[i][j - 1]) > fabs(map[i - 1][j]) )
        map[i][j] += map[i][j - 1]*mask[i - margin][j - margin];
      else
        map[i][j] += map[i - 1][j]*mask[i - margin][j - margin];
    }
    else
    {
      if (_random(0, 100) > clusterChance)
        map[i][j] = map[i][j] + _random(min, max);
      else if ( fabs(map[i][j - 1]) > fabs(map[i - 1][j]) )
        map[i][j] += map[i][j - 1];
      else
        map[i][j] += map[i - 1][j];
    }

    it++;
  }
}

/**
 * alternateClusterFilter
 *
 * @access public
 * @param int radius promien obszaru wokol biezacego piksela, ktory jest modyfikowanym jesli 0, to modyfikowany jest tylko
 *            biezacy piksel
 * @returns void
 * @author TSz
 */
void HeightmapCore::alternateClusterFilter(int radius)
{
  dirty = true;

	if (radius > margin)
		radius = margin;

  vector<int> clusteringSequence;
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
      clusteringSequence.push_back(j + i*width);

  random_shuffle(clusteringSequence.begin(), clusteringSequence.end());

  vector<int>::iterator it = clusteringSequence.begin();  
  while (it != clusteringSequence.end()) {
    int i = (*it)/width + margin;
    int j = (*it)%width + margin;

    //ustal kierunek
    int dir = rand()%4;

    int iSrc = i;
    int jSrc = j;
    switch (dir) {
      case 0:
  			if (fabs(map[i][j - 1]) > fabs(map[i - 1][j]))
          jSrc--;
        else
          iSrc--;

        break;

      case 1:
  			if (fabs(map[i][j + 1]) > fabs(map[i - 1][j]))
          jSrc++;
        else
          iSrc--;

        break;

      case 2:
  			if (fabs(map[i][j - 1]) > fabs(map[i + 1][j]))
          jSrc--;
        else
          iSrc++;

        break;

      case 3:
  			if (fabs(map[i][j + 1]) > fabs(map[i + 1][j]))
          jSrc++;
        else
          iSrc++;

        break;

      default:
        printf("err %d\n", dir);
        break;
    }

    float src = map[iSrc][jSrc];
    if (hasMask()) 
    {
      float srcWeight = 0.5;
      for (int ii = -radius; ii <= radius; ++ii)
        for (int jj = -radius; jj <= radius; ++jj) {
          srcWeight = 0.5*mask[i + ii - margin][j + jj - margin];
          map[i + ii][j + jj] = (1. - srcWeight)*map[i + ii][j + jj] + srcWeight*src;
        }
    }
    else
    {
      for (int ii = -radius; ii <= radius; ++ii)
        for (int jj = -radius; jj <= radius; ++jj) 
          map[i + ii][j + jj] = (map[i + ii][j + jj] + src)/2.;
    }

    it++;
  }
} 

void HeightmapCore::clusterFilter(int radius)
{
  dirty = true;

	if (radius > margin)
		radius = margin;

	list<float> tmpList;
	for (int i = margin; i <= realHeight - (margin + 1); ++i)
	{
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
		{
			tmpList.clear();
			float tmp;
			for (int ii = -radius; ii <= radius; ++ii)
				for (int jj = -radius; jj <= radius; ++jj)
					tmpList.push_back(map[i+ii][j+jj]);

			if ( fabs( *min_element(tmpList.begin(), tmpList.end()) ) > fabs( *max_element(tmpList.begin(), tmpList.end()) ) )
				tmp = *min_element(tmpList.begin(), tmpList.end());
			else
				tmp = *max_element(tmpList.begin(), tmpList.end());

      if (hasMask()) 
      {
        float tmpWeight = 0.5*mask[i - margin][j - margin];
        map[i][j] = (1. - tmpWeight)*map[i][j] + tmpWeight*tmp;
      }
      else
      {
        map[i][j] = (map[i][j] + tmp) / 2;
      }
    }
	}
}

void HeightmapCore::liquidFilter(float c, float d, float t,
                                 float u, bool wrap)
{
  dirty = true;

	vector<vector<float> > buffer(map);

	float coefA = ((4 - 8*c*c*t*t/(d*d))/(u*t+2));
	float coefB = ((u*t-2)/(u*t+2));
	float coefC = ((2*c*c*t*t)/(d*d))/(u*t+2);

  if (hasMask()) 
  {
    for (int i = margin; i <= realHeight - (margin + 1); ++i)
      for (int j = margin; j <= realWidth - (margin + 1); ++j)
      {
        float p1 = coefA * map[i][j];
        float p2 = coefB * buffer[i][j];
        float p3 = coefC * (map[i+1][j] + map[i-1][j] + map[i][j+1] + map[i][j-1]);

        float w = mask[i - margin][j - margin];
        buffer[i][j] = (1 - w)*buffer[i][j] + w*(p1 + p2 + p3);
      }
  }
  else
  {
    for (int i = margin; i <= realHeight - (margin + 1); ++i)
      for (int j = margin; j <= realWidth - (margin + 1); ++j)
      {
        float p1 = coefA * map[i][j];
        float p2 = coefB * buffer[i][j];
        float p3 = coefC * (map[i+1][j] + map[i-1][j] + map[i][j+1] + map[i][j-1]);
        buffer[i][j] = p1 + p2 + p3;
      }
  }

	map.swap(buffer);

	if (wrap)
		wrapEdges();
}

void HeightmapCore::smoothFilter(int radius, bool wrap)
{
  dirty = true;

	if (radius > margin)
		radius = margin;

	float div = ((2*radius+1)*(2*radius+1));

  vector<int> sequence;
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
      sequence.push_back(j + i*width);

  random_shuffle(sequence.begin(), sequence.end());

  vector<int>::iterator it = sequence.begin();  
  while (it != sequence.end()) {
    int i = (*it)/width + margin;
    int j = (*it)%width + margin;

    float temp = 0;

    for (int ii = -radius; ii <= radius; ++ii)
      for (int jj = -radius; jj <= radius; ++jj)
        temp += map[i+ii][j+jj];

    if (hasMask()) 
      map[i][j] = mask[i - margin][j - margin] * temp / div;
    else
      map[i][j] = temp / div;

    it++;
  }

	if (wrap)
		wrapEdges();
}

//nie skonczone, ani sprawdzone!!!
void HeightmapCore::terraceFilter(int levels)
{
	float min = getMin();
	float max = getMax();
	for (int i = margin; i <= realHeight - (margin + 1); ++i)
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
			map[i][j] = round((map[i][j] - min)/(max - min)*levels)/levels*(max - min) + min;

  dirty = true;
}

void HeightmapCore::walkerFilter(int incStep, int decStep, bool wrap)
{
  dirty = true;

	// pozycja startowa
	int y = int(_random(margin, margin + height - 1));
	int x = int(_random(margin, margin + width - 1));

	// dlugosc zycia
	int lifeSpan = int(_random(width * height, 3 * width * height));

	int step;
	if (_random(0, 100) > 50)
		step = incStep;
	else
		step = decStep;

	for(int l = 0; l < lifeSpan; ++l)
	{
    if (hasMask())
  		map[y][x] += mask[y - margin][x - margin]*step;
    else
      map[y][x] += step;

		int direction = int(_random(0, 4));
		switch (direction)
		{
			case 0: // gora
				if (y == margin && !wrap) return;
				if (y == margin && wrap) y = margin + height - 1;
				else y -= 1;
				break;
			case 1: // prawo
				if (x == margin + width - 1 && !wrap) return;
				if (x == margin + width - 1 && wrap) x = margin;
				else x += 1;
				break;
			case 2: // dol
				if (y == margin + height - 1 && !wrap) return;
				if (y == margin + height - 1 && wrap) y = margin;
				else y += 1;
				break;
			case 3: // lewo
				if (x == margin && !wrap) return;
				if (x == margin && wrap) x = margin + width - 1;
				else x -= 1;
				break;
			default:
				cout << "Cos dziwnego wypadlo. Direction walkera: " << direction << endl;
		}
	}

	if (wrap) wrapEdges();
}

void HeightmapCore::faultingFilter(int incStep, int decStep, bool wrap)
{
  dirty = true;

	int radius = lround(_random(1, fmin(width, height)/2));
	//cout << "radius: " << radius << endl;

	int sx, sy; // wspolrzedne srodka okregu
	sx = radius + // srodek nie moze byc blizej krawedzi niz radius
	lround(_random(0, 3*width - 1 - 2*radius)) - width;
	sy = radius + lround(_random(0, 3*height - 1 - 2*radius)) - height;
	//cout << "sx: " << sx << ", sy: " << sy << endl;

	int step;
	if (_random(0, 1) < .5) step = incStep;
	else step = decStep;
	//cout << "step: " << step << endl;

	for (int i = -radius; i <= radius; ++i)
		for (int j = -radius; j <= radius; ++j)
		{
			//cout << "checking point " << sx+j << ", " << sy+i << endl;
			//cout << "pow(fabs((sy+i) - sy), 2) + pow(fabs((sx+j) - sx), 2): " << pow(fabs((sy+i) - sy), 2) + pow(fabs((sx+j) - sx), 2) << endl;
			int posX, posY;
			if (pow(abs(i), 2) + pow(abs(j), 2) <= pow(abs(radius), 2))
			{
				posX = sx + j;
				posY = sy + i;
				if (posX < 0 && wrap)       posX += height;
				else if (posX < 0)          continue;
				if (posX >= height && wrap) posX -= height;
				else if (posX >= height)    continue;
				if (posY < 0 && wrap)       posY += width;
				else if (posY < 0)          continue;
				if (posY >= width && wrap)  posY -= width;
				else if (posY >= width)     continue;

        if (hasMask())
				  map[margin+posY][margin+posX] += mask[posY][posX]*step;
        else
				  map[margin+posY][margin+posX] += step;
			}
		}

	if (wrap) wrapEdges();
}

void HeightmapCore::wrapEdges()
{
  dirty = true;

/* wzor postepowania:
	vector<vector<float> >::iterator fromBegin = map.begin() + margin;
	vector<vector<float> >::iterator fromEnd = fromBegin + margin;
	vector<vector<float> >::iterator toDest = map.end() - margin;
	std::copy(fromBegin, fromEnd, toDest);
*/
	// zawiniecie pionowe
	copy(map.begin() + margin, map.begin() + 2*margin, map.end() - margin);
	copy(map.rbegin() + margin, map.rbegin() + 2*margin, map.rend() - margin);

	// zawiniecie poziome
	for (int i = 0; i < realHeight; ++i) {
		copy(map[i].begin() + margin, map[i].begin() + 2*margin, map[i].end() - margin);
		copy(map[i].rbegin() + margin, map[i].rbegin() + 2*margin, map[i].rend() - margin);
	}
}

float HeightmapCore::getMax()
{
  if (! dirty) return cachedMax;
  this->_minmax();
  return cachedMax;
}

float HeightmapCore::getMin()
{
  if (! dirty) return cachedMin;
  this->_minmax();
  return cachedMin;
}

void HeightmapCore::normalize() {
	normalize(getMax(), getMin());
}

void HeightmapCore::join(HeightmapCore & neighbour, Direction edge) {
  dirty = true;

	if ((getWidth() != neighbour.getWidth()) || (getHeight() != neighbour.getHeight()))
		return;

	int joinRange = (int)(height/3.);
	if (! joinRange)
		return;
		
	//cout << "join range: " << joinRange << endl;
		
	int neighbourWidth = neighbour.getWidth();
	int neighbourHeight = neighbour.getHeight();
	switch (edge)
	{
		case HE_E:
		case HE_W:
			for (int i = 0; i < height; ++i) {
				float modifiedRange = joinRange*(0.5 + 0.5*pow(sin(2.*M_PI*i/height), 2));
				for (int j = 0; j < modifiedRange; ++j) {
					float selfW = 0.5 + (j + 1.)/2./modifiedRange;
					float neighbourW = 1. - selfW;
				
					if (edge == HE_E) {
						float newSelfVal = selfW*getPixel(width - 1 - j, i) + neighbourW*neighbour.getPixel(neighbourWidth - 1 - j, i);
						float newNeighbourVal = selfW*neighbour.getPixel(j, i) + neighbourW*getPixel(j, i);			
					
						setPixel(width - 1 - j, i, newSelfVal);
						neighbour.setPixel(j, i, newNeighbourVal);
					}
					else {
						float newSelfVal = selfW*getPixel(j, i) + neighbourW*neighbour.getPixel(j, i);
						float newNeighbourVal = selfW*neighbour.getPixel(neighbourWidth - 1 - j, i) + neighbourW*getPixel(neighbourWidth - 1 - j, i);			
					
						setPixel(j, i, newSelfVal);
						neighbour.setPixel(neighbourWidth - 1 - j, i, newNeighbourVal);
					}
				}
			}
		
			break;
			
		case HE_N:
		case HE_S:
			for (int j = 0; j < width; ++j) {
				float modifiedRange = joinRange*(0.5 + 0.5*pow(sin(2.*M_PI*j/width), 2));
				for (int i = 0; i < modifiedRange; ++i) {
					float selfW = 0.5 + (i + 1.)/2./modifiedRange;
					float neighbourW = 1. - selfW;
				
					if (edge == HE_S) {
						float newSelfVal = selfW*getPixel(j, height - 1 - i) + neighbourW*neighbour.getPixel(j, neighbourHeight - 1 - i);
						float newNeighbourVal = selfW*neighbour.getPixel(j, i) + neighbourW*getPixel(j, i);			
					
						setPixel(j, height - 1 - i, newSelfVal);
						neighbour.setPixel(j, i, newNeighbourVal);
					} else {
						float newSelfVal = selfW*getPixel(j, i) + neighbourW*neighbour.getPixel(j, i);
						float newNeighbourVal = selfW*neighbour.getPixel(j, neighbourHeight - 1 - i) + neighbourW*getPixel(j, neighbourHeight - 1 - i);			
					
						setPixel(j, i, newSelfVal);
						neighbour.setPixel(j, neighbourHeight - 1 - i, newNeighbourVal);
					}
				}
			}
		
			break;
	}
}

void HeightmapCore::normalize(float max, float min)
{
  dirty = true;

	if (min == max) {
		vector<float> tmp(realWidth, .5);
		map = vector<vector<float> >(realHeight, tmp);
	}
	else {
		for (int i = 0; i < realHeight; ++i)
			for (int j = 0; j < realWidth; ++j) {
				map[i][j] = (map[i][j] - min) / (max - min);
				//map[i][j] = floor(map[i][j] * 255);
			}
	}
}

bool HeightmapCore::hasMask() const
{
  return (mask.size() == height && mask[0].size() == width);
}

float HeightmapCore::_random(float min, float max) const
{
// funkcja przeskalowujaca dowolny przedzial na <0,1>
	const float P[] = {0., min}; // punkt P, dwa miejsca tablicy - dwie wspolrzedne
	const float Q[] = {1., max};

	float a = (P[1] - Q[1]) / -1.;
	float b = Q[1] - a * Q[0];

	return a * rand()/RAND_MAX + b;
}

bool HeightmapCore::_isValidPixel(int x, int y) const
{
	return x < width && y < height;
}

void HeightmapCore::_minmax() {
  if (! dirty) return;

  cachedMin = cachedMax = map[margin][margin];
	for (int i = margin; i <= realHeight - (margin + 1); ++i)
		for (int j = margin; j <= realWidth - (margin + 1); ++j) {
      if (map[i][j] < cachedMin) cachedMin = map[i][j];
      if (map[i][j] > cachedMax) cachedMax = map[i][j];
    }

  dirty = false;
}
