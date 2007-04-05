#ifndef LIQUIDFILTERCONTROL_H
#define LIQUIDFILTERCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;

class LiquidFilterControl : public QWidget
{
	Q_OBJECT

	public:
	LiquidFilterControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox*       cSpin;
	QSpinBox*       dSpin;
	QDoubleSpinBox* tSpin;
	QSpinBox*       uSpin;
	QSpinBox*       itersSpin;
	QCheckBox*      wrapCheck;
};

#endif
