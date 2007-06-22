#ifndef SCROLLMAPPREVIEW_H
#define SCROLLMAPPREVIEW_H

#include <QScrollArea>

#include "MapPreview.h"
#include "Heightmap.h"

class QWidget;

class ScrollMapPreview : public QScrollArea
{
	Q_OBJECT

	public:
	ScrollMapPreview(QWidget* parent = 0);
	void setMap(Heightmap* hgen);

	signals:
	void mouseAt(int x, int y);

	private:
	MapPreview interior;
};

#endif
