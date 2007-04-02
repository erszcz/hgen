#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QToolTip>

#include "MapPreview.h"
#include "Heightmap.h"

// temp
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
// fin

MapPreview::MapPreview(QWidget* parent)
	: QWidget(parent)
{
	gen = 0;
	setAttribute(Qt::WA_StaticContents);
	setFixedSize(600, 600);

	setMouseTracking(true);
}

void MapPreview::setMap(Heightmap* hgen)
{
	if(gen)
		disconnect(gen, 0, 0, 0);
	gen = hgen;
	connect(gen, SIGNAL(mapChanged()), this, SLOT(repaint()));

	update();
}

void MapPreview::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter(this);
	painter.setBackground(QBrush(Qt::Dense1Pattern));
	painter.eraseRect(rect());
	if(gen)
	{
		QPixmap temp = QPixmap::fromImage(gen->getImage());
		painter.drawPixmap(temp.rect(), temp, temp.rect());
	}
}

void MapPreview::mouseMoveEvent(QMouseEvent* /*event*/)
{
	int posX = mapFromGlobal(QCursor::pos()).x();
	int posY = mapFromGlobal(QCursor::pos()).y();
	if(posX >= 0 && posX <= width() && posY >= 0 && posY <= height())
		emit mouseAt(posX, posY);
	else
		emit mouseAt(-1, -1);
}
