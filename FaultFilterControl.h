#ifndef FAULTFILTERCONTROL_H
#define FAULTFILTERCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;
class QCheckBox;

class FaultFilterControl : public QWidget
{
	Q_OBJECT

	public:
	FaultFilterControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox* itersSpin;
	QSpinBox* incStepSpin;
	QSpinBox* decStepSpin;
	QCheckBox* wrapCheck;
};

#endif
