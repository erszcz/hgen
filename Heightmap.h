#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <QObject>
#include <QTime>
#include <QImage>
#include <QSize>

#include "HeightmapCore.h"

class QString;

class HAction;

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
  void performHAction(HAction* action);

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
