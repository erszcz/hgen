#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>

#include "SmoothFilterControl.h"

SmoothFilterControl::SmoothFilterControl(QWidget* parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);


	QLabel* itersLabel = new QLabel("Iterations:");
	itersSpin = new QSpinBox;
	itersSpin->setRange(0, 5000);
	itersSpin->setValue(10);
	itersSpin->setAccelerated(true);

	layout->addWidget(itersLabel, 0, 0);
	layout->addWidget(itersSpin, 0, 1);


	QLabel* radiusLabel = new QLabel("Radius:");
	radiusSpin = new QSpinBox;
	radiusSpin->setRange(0, 20);
	radiusSpin->setValue(2);

	layout->addWidget(radiusLabel, 1, 0);
	layout->addWidget(radiusSpin, 1, 1);


	wrapCheck = new QCheckBox("Wrap map edges");
	wrapCheck->setTristate(false);
	wrapCheck->setChecked(true);

	layout->addWidget(wrapCheck, 2, 0);


	QPushButton* go = new QPushButton("&Go!");
	connect(go, SIGNAL(clicked()), this, SLOT(activate()));

	layout->addWidget(go, 2, 1);
}

void SmoothFilterControl::activate()
{
	emit activated(itersSpin->value(), radiusSpin->value(), wrapCheck->isChecked());
}
