#ifndef ALTERNATECLUSTERFILTERCONTROL_H
#define ALTERNATECLUSTERFILTERCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;

class AlternateClusterFilterControl : public QWidget
{
	Q_OBJECT

	public:
	AlternateClusterFilterControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox* radiusSpin;
};

#endif
