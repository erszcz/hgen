#ifndef MAPPREVIEW_H
#define MAPPREVIEW_H

#include <QWidget>
#include <QImage>

#include "Heightmap.h"

class QWidget;

class MapPreview : public QWidget
{
	Q_OBJECT

	public:
	MapPreview(QWidget* parent = 0);
	void setMap(Heightmap* hgen);

	signals:
	void mouseAt(int x, int y);

	protected:
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

	private:
	Heightmap* gen;
};

#endif
