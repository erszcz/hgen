#ifndef WALKERFILTERCONTROL_H
#define WALKERFILTERCONTROL_H

#include <QWidget>

class QSpinBox;
class QCheckBox;

class WalkerFilterControl : public QWidget
{
	Q_OBJECT

	public:
	WalkerFilterControl(QWidget* parent = 0);

	signals:
	void activated(short count, short incStep, short decStep, bool wrap);

	private slots:
	void activate();

	private:
	QSpinBox* countSpin;
	QSpinBox* incStepSpin;
	QSpinBox* decStepSpin;
	QCheckBox* wrapCheck;
};

#endif
