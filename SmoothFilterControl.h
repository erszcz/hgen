#ifndef SMOOTHFILTERCONTROL_H
#define SMOOTHFILTERCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;
class QCheckBox;

class SmoothFilterControl : public QWidget
{
	Q_OBJECT

	public:
	SmoothFilterControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox*       itersSpin;
	QSpinBox*       radiusSpin;
	QCheckBox*      wrapCheck;
};

#endif
