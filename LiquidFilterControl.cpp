#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>

#include "LiquidFilterControl.h"

LiquidFilterControl::LiquidFilterControl(QWidget* parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);


	QLabel* cLabel = new QLabel("Wave speed:");
	cSpin = new QSpinBox;
	cSpin->setRange(0, 1000);
	cSpin->setValue(100);
	cSpin->setAccelerated(true);

	layout->addWidget(cLabel, 0, 0);
	layout->addWidget(cSpin, 0, 1);


	QLabel* dLabel = new QLabel("Node distance:");
	dSpin = new QSpinBox;
	dSpin->setRange(0, 100);
	dSpin->setValue(10);
	dSpin->setAccelerated(true);

	layout->addWidget(dLabel, 1, 0);
	layout->addWidget(dSpin, 1, 1);


	QLabel* tLabel = new QLabel("Time step:");
	tSpin = new QDoubleSpinBox;
	tSpin->setDecimals(3);
	tSpin->setRange(0., .2);
	tSpin->setSingleStep(.001);
	tSpin->setValue(.033);
	tSpin->setAccelerated(true);

	layout->addWidget(tLabel, 2, 0);
	layout->addWidget(tSpin, 2, 1);


	QLabel* uLabel = new QLabel("Fluid viscosity:");
	uSpin = new QSpinBox;
	uSpin->setRange(0, 1000);
	uSpin->setValue(100);
	uSpin->setAccelerated(true);

	layout->addWidget(uLabel, 3, 0);
	layout->addWidget(uSpin, 3, 1);


	QLabel* itersLabel = new QLabel("Iterations:");
	itersSpin = new QSpinBox;
	itersSpin->setRange(0, 10000);
	itersSpin->setValue(100);
	itersSpin->setAccelerated(true);

	layout->addWidget(itersLabel, 4, 0);
	layout->addWidget(itersSpin, 4, 1);


	wrapCheck = new QCheckBox("Wrap map edges");
	wrapCheck->setTristate(false);
	wrapCheck->setChecked(true);

	layout->addWidget(wrapCheck, 5, 0);


	QPushButton* go = new QPushButton("&Go!");
	connect(go, SIGNAL(clicked()), this, SLOT(activate()));

	layout->addWidget(go, 5, 1);
}

void LiquidFilterControl::activate()
{
	emit activated(double(cSpin->value()), double(dSpin->value()),
	               tSpin->value(), double(uSpin->value()),
								 itersSpin->value(), wrapCheck->isChecked());
}
