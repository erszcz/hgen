#ifndef HEIGHTMAPMATRIX_H
#define HEIGHTMAPMATRIX_H

#include <QObject>
#include <QTime>
#include <QImage>
#include <QSize>

#include "HeightmapMatrixCore.h"

class HeightmapMatrix : public QObject
{
	Q_OBJECT

	public:
	HeightmapMatrix(int cols, int rows, int mapWidth, int mapHeight, int mapMargin = 1);
	~HeightmapMatrix() { }

	QSize getSize() const;
	QImage getImage() const;
	
	HeightmapMatrixCore & getCore();

	signals:
	void mapChanged(QImage newMap);

	private:
	void _checkTime();

	QTime timer;
	HeightmapMatrixCore internalMatrix;
};

#endif
