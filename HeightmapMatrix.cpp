#include <QApplication>
#include <QImage>
#include <QTime>
#include <QSize>

#include "HeightmapMatrixCore.h"
#include "HeightmapMatrix.h"

HeightmapMatrix::HeightmapMatrix(int cols, int rows, int mapWidth, int mapHeight, int mapMargin)
	: QObject(),
	  timer(0, 0, 0, 0),
	  internalMatrix(cols, rows, mapWidth, mapHeight, mapMargin)
{
	timer.start();
}

QImage HeightmapMatrix::getImage() const
{
	HeightmapMatrixCore temp(internalMatrix);
	temp.normalize();
	
	QSize size = getSize();
	QImage img(size, QImage::Format_Indexed8);
	
	img.setNumColors(256);
	for (int l = 0; l < 256; ++l)
		img.setColor(l, qRgb(l, l, l));
		
	int mapWidth = temp.getMapWidth();
	int mapHeight = temp.getMapHeight();
	int cols = temp.getCols();
	int rows = temp.getRows();
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++) {
			HeightmapCore e = temp.getElement(i, j);
			for (int y = 0; y < mapHeight; ++y)
				for (int x = 0; x < mapWidth; ++x)
					img.setPixel(x + i*mapWidth, y + j*mapHeight, int(255 * e.getPixel(x, y)));
		}
			
	return img;
}

void HeightmapMatrix::_checkTime()
{
	if(timer.restart() >= 40)
		emit mapChanged(getImage());
}

QSize HeightmapMatrix::getSize() const
{
	int mapWidth = internalMatrix.getMapWidth();
	int mapHeight = internalMatrix.getMapHeight();
	return QSize(internalMatrix.getCols()*mapWidth, internalMatrix.getRows()*mapHeight);
}

HeightmapMatrixCore & HeightmapMatrix::getCore()
{
	return internalMatrix;
}

