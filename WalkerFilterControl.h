#ifndef WALKERFILTERCONTROL_H
#define WALKERFILTERCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;
class QCheckBox;

class WalkerFilterControl : public QWidget
{
	Q_OBJECT

	public:
	WalkerFilterControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox* countSpin;
	QSpinBox* incStepSpin;
	QSpinBox* decStepSpin;
	QCheckBox* wrapCheck;
};

#endif
