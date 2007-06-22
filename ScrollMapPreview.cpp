#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QToolTip>

#include "ScrollMapPreview.h"
#include "Heightmap.h"

// temp
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
// fin

ScrollMapPreview::ScrollMapPreview(QWidget* parent)
	: QScrollArea(parent)
{
	setAttribute(Qt::WA_StaticContents);
	setFixedSize(600, 600);

  QPalette pal(palette());
  pal.setBrush(QPalette::Background, QBrush(Qt::Dense1Pattern));
  setPalette(pal);

  setWidget(&interior);
}

void ScrollMapPreview::setMap(Heightmap* hgen)
{
  interior.setMap(hgen);
  interior.resize(hgen->getWidth(), hgen->getHeight());

  connect(&interior, SIGNAL(mouseAt(int, int)), this, SIGNAL(mouseAt(int, int))); 

	update();
}

