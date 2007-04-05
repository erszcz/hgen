#ifndef CLUSTERFILTERCONTROL_H
#define CLUSTERFILTERCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;

class ClusterFilterControl : public QWidget
{
	Q_OBJECT

	public:
	ClusterFilterControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox* radiusSpin;
};

#endif
