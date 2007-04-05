#include <QApplication>
#include <QImage>
#include <QTime>
#include <QSize>
#include <QString>

#include "HeightmapCore.h"
#include "Heightmap.h"
#include "HAction.h"

//
#include <iostream>
//

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

void Heightmap::performHAction(HAction* action)
{
  std::cout << "dupa1" << endl;
	emit processingStarted();
  
  int iters = action->iterations();
  std::cout << "iters: " << iters << endl;
	for(int i = -1; i < iters; ++i)
	{
    std::cout << "dupa2" << endl;
    if (i == -1) iters = 0 | (iters - 1);

    switch (action->type())
    {
      case HAction::randomFill:
        internalMap.randomFill(action->minimum(), action->maximum());
        break;
      case HAction::clusterFill:
        internalMap.clusterFill(action->minimum(),
                                action->maximum(),
                                action->chance(),
                                action->radius());
        break;
      case HAction::clusterFilter:
        internalMap.clusterFilter(action->radius());
        break;
      case HAction::alternateClusterFilter:
        internalMap.alternateClusterFilter(action->radius());
        break;
      case HAction::liquidFilter:
        internalMap.liquidFilter(action->waveSpeed(),
                                 action->nodeDistance(),
                                 action->timeStep(),
                                 action->viscosity(),
                                 action->wrap());
        break;
      case HAction::smoothFilter:
        internalMap.smoothFilter(action->radius(), action->wrap());
        break;
      case HAction::walkerFilter:
        internalMap.walkerFilter(action->incStep(),
                                 action->decStep(),
                                 action->wrap());
        break;
      case HAction::faultingFilter:
        internalMap.faultingFilter(action->incStep(),
                                   action->decStep(),
                                   action->wrap());
        break;
    }
    
		_checkTime();
	}

  delete action;

	emit mapChanged();
	emit processingFinished();
}

bool Heightmap::saveToDisk(QString filename)
{
	return getImage().save(filename, 0, 100);
}
