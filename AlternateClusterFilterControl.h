#ifndef ALTERNATECLUSTERFILTERCONTROL_H
#define ALTERNATECLUSTERFILTERCONTROL_H

#include <QWidget>

class QSpinBox;

class AlternateClusterFilterControl : public QWidget
{
	Q_OBJECT

	public:
	AlternateClusterFilterControl(QWidget* parent = 0);

	signals:
	void activated(short radius);

	private slots:
	void activate();

	private:
	QSpinBox* radiusSpin;
};

#endif
