#ifndef CLUSTERFILTERCONTROL_H
#define CLUSTERFILTERCONTROL_H

#include <QWidget>

class QSpinBox;

class ClusterFilterControl : public QWidget
{
	Q_OBJECT

	public:
	ClusterFilterControl(QWidget* parent = 0);

	signals:
	void activated(short radius);

	private slots:
	void activate();

	private:
	QSpinBox* radiusSpin;
};

#endif
