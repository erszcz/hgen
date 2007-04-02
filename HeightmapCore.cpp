#include <cstdlib>
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

	// inicjalizacja mapy
	vector<double> tmp(realWidth, 0.);
	map = vector<vector<double> >(realHeight, tmp);
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

	map = vector<vector<double> >(old.map);
}

double HeightmapCore::getPixel(int x, int y) const
{
	return map[margin + y][margin + x];
}

bool HeightmapCore::setPixel(int x, int y, double value)
{
	if ((x > width - 1) || (y > height -1))
		return false;

	map[y + margin][x + margin] = value;
	return true;
}

void HeightmapCore::flatFill(double v)
{
	for (int i = margin; i < margin + height; ++i)
		for (int j = margin; j < margin + width; ++j)
			map[i][j] = v;
}

void HeightmapCore::randomFill(double min, double max)
{
	for (int i = margin; i <= realHeight - (margin + 1); ++i)
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
			map[i][j] = map[i][j] + _random(min, max);
}

/*void HeightmapCore::clusterFill(double min, double max,
                                short clusterChance, short radius)
{
	if (radius > margin)
		radius = margin;
	list<double> tmpList;
	for (int i = margin; i <= realHeight - (margin + 1); ++i)
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
			if (_random(0, 100) > clusterChance)
				map[i][j] = map[i][j] + _random(min, max);
			else {
				for (short ii = -radius; ii <= radius; ++ii)
					for (short jj = -radius; jj <= radius; ++jj)
						tmpList.push_back(map[i+ii][j+jj]);
				if ( fabs( *min_element(tmpList.begin(), tmpList.end()) ) >  *max_element(tmpList.begin(), tmpList.end()) )
					map[i][j] = map[i][j] + *min_element(tmpList.begin(), tmpList.end());
				else
					map[i][j] = map[i][j] + *max_element(tmpList.begin(), tmpList.end());
				tmpList.clear();
			}
}*/

void HeightmapCore::clusterFill(double min, double max,
                                short clusterChance, short radius)
{
	if (radius > margin)
		radius = margin;
	for (int i = margin; i <= realHeight - (margin + 1); ++i)
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
			if (_random(0, 100) > clusterChance)
				map[i][j] = map[i][j] + _random(min, max);
			else if ( fabs(map[i][j - 1]) > fabs(map[i - 1][j]) )
				map[i][j] += map[i][j - 1];
			else
				map[i][j] += map[i - 1][j];
				
}

/**
 * alternateClusterFilter
 *
 * @access public
 * @param short radius promien obszaru wokol biezacego piksela, ktory jest modyfikowanym jesli 0, to modyfikowany jest tylko
 *            biezacy piksel
 * @returns void
 * @author TSz
 */
void HeightmapCore::alternateClusterFilter(short radius)
{
	if (radius > margin)
		radius = margin;

  vector<int> clusteringSequence;
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
      clusteringSequence.push_back(j + i*height);

  random_shuffle(clusteringSequence.begin(), clusteringSequence.end());

  vector<int>::iterator it = clusteringSequence.begin();  
  while (it != clusteringSequence.end()) {
    int i = (*it)/height + margin;
    int j = (*it)%height + margin;

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

    double src = map[iSrc][jSrc];
    for (int ii = -radius; ii <= radius; ++ii)
      for (int jj = -radius; jj <= radius; ++jj) 
        map[i + ii][j + jj] = (map[i + ii][j + jj] + src)/2.;

    it++;
  }
} 

void HeightmapCore::clusterFilter(int radius)
{
	if (radius > margin)
		radius = margin;
	list<double> tmpList;
	for (int i = margin; i <= realHeight - (margin + 1); ++i)
	{
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
		{
			tmpList.clear();
			double tmp;
			for (short ii = -radius; ii <= radius; ++ii)
				for (short jj = -radius; jj <= radius; ++jj)
					tmpList.push_back(map[i+ii][j+jj]);
			if ( fabs( *min_element(tmpList.begin(), tmpList.end()) ) > fabs( *max_element(tmpList.begin(), tmpList.end()) ) )
				tmp = *min_element(tmpList.begin(), tmpList.end());
			else
				tmp = *max_element(tmpList.begin(), tmpList.end());
			map[i][j] = (map[i][j] + tmp) / 2;
		}
	}
}

void HeightmapCore::liquidFilter(double c, double d, double t,
                                 double u, bool wrap)
{
	vector<vector<double> > buffer(map);

	double coefA = ((4 - 8*c*c*t*t/(d*d))/(u*t+2));
	double coefB = ((u*t-2)/(u*t+2));
	double coefC = ((2*c*c*t*t)/(d*d))/(u*t+2);

	for (int i = margin; i <= realHeight - (margin + 1); ++i)
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
		{
			double p1 = coefA * map[i][j];
			double p2 = coefB * buffer[i][j];
			double p3 = coefC * (map[i+1][j] + map[i-1][j] + map[i][j+1] + map[i][j-1]);
			buffer[i][j] = p1 + p2 + p3;
		}

	map.swap(buffer);

	if (wrap)
		wrapEdges();
}

void HeightmapCore::smoothFilter(short radius, bool wrap)
{
	if (radius > margin)
		radius = margin;
	
	double div = ((2*radius+1)*(2*radius+1));

	for (int i = margin; i <= realHeight - (margin + 1); ++i)
		for (int j = margin; j <= realWidth - (margin + 1); ++j)
		{
			double temp = 0;

			for (short ii = -radius; ii <= radius; ++ii)
				for (short jj = -radius; jj <= radius; ++jj)
					temp += map[i+ii][j+jj];

			map[i][j] = temp / div;
		}

	if (wrap)
		wrapEdges();
}

void HeightmapCore::walkerFilter(int incStep, int decStep, bool wrap)
{
	// pozycja startowa
	int y = int(_random(margin, margin + height - 1));
	int x = int(_random(margin, margin + width - 1));

	// dlugosc zycia
	int lifeSpan = int(_random(width * height, 3 * width * height));

	short step;
	if (_random(0, 100) > 50)
		step = incStep;
	else
		step = -decStep;

	for(int l = 0; l < lifeSpan; ++l)
	{
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

				map[margin+posY][margin+posX] += step;
			}
		}

	if (wrap) wrapEdges();
}

void HeightmapCore::wrapEdges()
{
/* wzor postepowania:
	vector<vector<double> >::iterator fromBegin = map.begin() + margin;
	vector<vector<double> >::iterator fromEnd = fromBegin + margin;
	vector<vector<double> >::iterator toDest = map.end() - margin;
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

double HeightmapCore::getMax() const
{
	list<double> maxList;
	for (int i = 0; i < realHeight; ++i)
		maxList.push_back( *max_element(map[i].begin(), map[i].end()) );
	
	return *max_element(maxList.begin(), maxList.end());
}

double HeightmapCore::getMin() const
{
	list<double> minList;
	for (int i = 0; i < realHeight; ++i)
		minList.push_back( *min_element(map[i].begin(), map[i].end()) );
	
	return *min_element(minList.begin(), minList.end());
}

void HeightmapCore::normalize() {
	normalize(getMax(), getMin());
}

void HeightmapCore::normalize(double max, double min)
{
	if (min == max) {
		vector<double> tmp(realWidth, .5);
		map = vector<vector<double> >(realHeight, tmp);
	}
	else {
		for (int i = 0; i < realHeight; ++i)
			for (int j = 0; j < realWidth; ++j) {
				map[i][j] = (map[i][j] - min) / (max - min);
				//map[i][j] = floor(map[i][j] * 255);
			}
	}
}

double HeightmapCore::_random(double min, double max) const
{
// funkcja przeskalowujaca dowolny przedzial na <0,1>
	const double P[] = {0., min}; // punkt P, dwa miejsca tablicy - dwie wspolrzedne
	const double Q[] = {1., max};

	double a = (P[1] - Q[1]) / -1.;
	double b = Q[1] - a * Q[0];

	return a * rand()/RAND_MAX + b;
}

bool HeightmapCore::_isValidPixel(int x, int y) const
{
	return x < width && y < height;
}
