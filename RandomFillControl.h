#ifndef RANDOMFILLCONTROL_H
#define RANDOMFILLCONTROL_H

#include <QWidget>

#include "HAction.h"

class QSpinBox;

class RandomFillControl : public QWidget
{
	Q_OBJECT

	public:
	RandomFillControl(QWidget* parent = 0);

	signals:
	void activated(HAction* act);

	private slots:
	void activate();

	private:
	QSpinBox* minSpin;
	QSpinBox* maxSpin;
};

#endif
