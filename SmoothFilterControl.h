#ifndef SMOOTHFILTERCONTROL_H
#define SMOOTHFILTERCONTROL_H

#include <QWidget>

class QSpinBox;
class QCheckBox;

class SmoothFilterControl : public QWidget
{
	Q_OBJECT

	public:
	SmoothFilterControl(QWidget* parent = 0);

	signals:
	void activated(short iters, short radius, bool wrap);

	private slots:
	void activate();

	private:
	QSpinBox*       itersSpin;
	QSpinBox*       radiusSpin;
	QCheckBox*      wrapCheck;
};

#endif
