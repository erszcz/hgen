#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "WalkerFilterControl.h"

WalkerFilterControl::WalkerFilterControl(QWidget* parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);


	QLabel* countLabel = new QLabel("Number of walkers:");
	countSpin = new QSpinBox;
	countSpin->setRange(0, 50);
	countSpin->setValue(5);
	countSpin->setAccelerated(true);

	layout->addWidget(countLabel, 0, 0);
	layout->addWidget(countSpin, 0, 1);


	QLabel* incStepLabel = new QLabel("Incrementation step:");
	incStepSpin = new QSpinBox;
	incStepSpin->setRange(0, 500);
	incStepSpin->setValue(25);
	incStepSpin->setAccelerated(true);

	layout->addWidget(incStepLabel, 1, 0);
	layout->addWidget(incStepSpin, 1, 1);


	QLabel* decStepLabel = new QLabel("Decrementation step:");
	decStepSpin = new QSpinBox;
	decStepSpin->setRange(0, 500);
	decStepSpin->setValue(25);
	decStepSpin->setAccelerated(true);

	layout->addWidget(decStepLabel, 2, 0);
	layout->addWidget(decStepSpin, 2, 1);


	wrapCheck = new QCheckBox("Wrap map edges");
	wrapCheck->setTristate(false);
	wrapCheck->setChecked(true);

	layout->addWidget(wrapCheck, 3, 0);


	QPushButton* go = new QPushButton("&Go!");
	connect(go, SIGNAL(clicked()), this, SLOT(activate()));

	layout->addWidget(go, 3, 1);
}

void WalkerFilterControl::activate()
{
	emit activated(countSpin->value(), incStepSpin->value(),
	               decStepSpin->value(), wrapCheck->isChecked());
}
