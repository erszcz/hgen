#ifndef CLUSTERFILLCONTROL_H
#define CLUSTERFILLCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;

class ClusterFillControl : public QWidget
{
	Q_OBJECT

	public:
	ClusterFillControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox* minSpin;
	QSpinBox* maxSpin;
	QSpinBox* chanceSpin;
	QSpinBox* radiusSpin;
};

#endif
