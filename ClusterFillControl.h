#ifndef CLUSTERFILLCONTROL_H
#define CLUSTERFILLCONTROL_H

#include <QWidget>

class QSpinBox;

class ClusterFillControl : public QWidget
{
	Q_OBJECT

	public:
	ClusterFillControl(QWidget* parent = 0);

	signals:
	void activated(double min, double max,
	               short clusterChance, short radius);

	private slots:
	void activate();

	private:
	QSpinBox* minSpin;
	QSpinBox* maxSpin;
	QSpinBox* chanceSpin;
	QSpinBox* radiusSpin;
};

#endif
