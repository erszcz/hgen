#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <QObject>
#include <QTime>
#include <QImage>
#include <QSize>

#include "HeightmapCore.h"

class QString;

class Heightmap : public QObject
{
	Q_OBJECT

	public:
	Heightmap(uint height, uint width, uint margin);
	Heightmap(QString filename, uint height, uint width, uint margin);

	uint getHeight() const;
	uint getWidth() const;
	QSize getSize() const;

	QImage getImage() const;

	public slots:
	void randomFill(double min = -500., double max = 500.);

	void clusterFill(double min = -500., double max = 500.,
	                 short clusterChance = 60, short radius = 1);

	void clusterFilter(short radius = 1);
	void alternateClusterFilter(short radius = 0);

	void liquidFilter(double c = 100., double d = 10., double t = .033,
	                  double u = 100., short iters = 250, bool wrap = true);
	
	void smoothFilter(short iters, short radius, bool wrap);

	void walkerFilter(short count, short incStep, short decStep, bool wrap);

	void faultingFilter(short iters, short incStep, short decStep, bool wrap);

	void wrapEdges();

	void normalize();

	bool saveToDisk(QString filename);

	signals:
	void mapChanged();

	void processingStarted();
	void processingFinished();

	private:
	void _checkTime();

	QTime timer;
	HeightmapCore internalMap;
};

#endif
