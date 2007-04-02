#ifndef WRITER_H
#define WRITER_H

#include <QObject>

class Writer : public QObject
{
	Q_OBJECT

	public:
	Writer(QObject* parent = 0);
	~Writer() {}

	public slots:
	void randomFill(double min, double max);

	void clusterFill(double min, double max, short clusterChance, short radius);

	void clusterFilter(short radius);

	void liquidFilter(double c, double d, double t,
	                  double u, short iters, bool wrap);
};

#endif
