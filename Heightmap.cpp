#include <QApplication>
#include <QImage>
#include <QTime>
#include <QSize>
#include <QString>

#include "HeightmapCore.h"
#include "Heightmap.h"

Heightmap::Heightmap(uint width, uint height, uint margin)
	: QObject(),
	  timer(0, 0, 0, 0),
	  internalMap(height, width, margin)
{
	timer.start();
}

Heightmap::Heightmap(QString filename, uint width, uint height, uint margin)
	: QObject(),
	  timer(0, 0, 0, 0),
	  internalMap(height, width, margin)
{
	timer.start();
	QImage temp(filename);

	for(uint y = 0; y < temp.height(); ++y)
		for(uint x = 0; x < temp.width(); ++x)
		{
			internalMap.setPixel(x, y, 10 * qGray(temp.pixel(x, y)));
		}
}

QImage Heightmap::getImage() const
{
	HeightmapCore temp(internalMap);
	temp.normalize();

	QImage mapImg(temp.getWidth(), temp.getHeight(), QImage::Format_Indexed8);
	// ustawiamy palete barw
	mapImg.setNumColors(256);
	for (int l = 0; l < 256; ++l)
		mapImg.setColor(l, qRgb(l, l, l));
	// rysujemy mape
	for (uint y = 0; y < temp.getHeight(); ++y)
		for (uint x = 0; x < temp.getWidth(); ++x)
		{
			mapImg.setPixel(x, y, int(255 * temp.getPixel(x, y)));
		}
	return mapImg;
}

void Heightmap::_checkTime()
{
	if(timer.restart() >= 60)
	{
		QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		emit mapChanged();
	}
}

uint Heightmap::getHeight() const
{
	return internalMap.getHeight();
}

uint Heightmap::getWidth() const
{
	return internalMap.getWidth();
}

QSize Heightmap::getSize() const
{
	return QSize(internalMap.getWidth(), internalMap.getHeight());
}

void Heightmap::randomFill(double min, double max)
{
	emit processingStarted();

	internalMap.randomFill(min, max);
	emit mapChanged();

	emit processingFinished();
}

void Heightmap::clusterFill(double min, double max,
                            short clusterChance, short radius)
{
	emit processingStarted();

	internalMap.clusterFill(min, max, clusterChance, radius);
	emit mapChanged();

	emit processingFinished();
}

void Heightmap::clusterFilter(short radius)
{
	emit processingStarted();

	internalMap.clusterFilter(radius);
	emit mapChanged();

	emit processingFinished();
}

void Heightmap::alternateClusterFilter(short radius)
{
	emit processingStarted();

	internalMap.alternateClusterFilter(radius);
	emit mapChanged();

	emit processingFinished();
}

void Heightmap::liquidFilter(double c, double d, double t, double u,
                             short iters, bool wrap)
{
	emit processingStarted();

	for(int i = 0; i < iters; ++i)
	{
		internalMap.liquidFilter(c, d, t, u, wrap);
		_checkTime();
	}

	emit mapChanged();
	emit processingFinished();
}

void Heightmap::smoothFilter(short iters, short radius, bool wrap)
{
	emit processingStarted();

	for(int i = 0; i < iters; ++i)
	{
		internalMap.smoothFilter(radius, wrap);
		_checkTime();
	}

	emit mapChanged();
	emit processingFinished();
}

void Heightmap::walkerFilter(short count, short incStep, short decStep, bool wrap)
{
	emit processingStarted();

	for(int i = 0; i < count; ++ i)
	{
		internalMap.walkerFilter(incStep, decStep, wrap);
		_checkTime();
	}

	emit mapChanged();
	emit processingFinished();
}

void Heightmap::faultingFilter(short iters, short incStep, short decStep, bool wrap)
{
	emit processingStarted();

	for(int l = 0; l < iters; ++l)
	{
		internalMap.faultingFilter(incStep, decStep, wrap);
		_checkTime();
	}
	
	emit mapChanged();
	emit processingFinished();
}

void Heightmap::wrapEdges()
{
	internalMap.wrapEdges();
	emit mapChanged();
}

void Heightmap::normalize()
{
	internalMap.normalize();
	emit mapChanged();
}

bool Heightmap::saveToDisk(QString filename)
{
	return getImage().save(filename, 0, 100);
}
