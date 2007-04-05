#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "FaultFilterControl.h"
#include "HAction.h"

FaultFilterControl::FaultFilterControl(QWidget* parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);


	QLabel* itersLabel = new QLabel("Iterations:");
	itersSpin = new QSpinBox;
	itersSpin->setRange(0, 10000);
	itersSpin->setValue(1000);
	itersSpin->setAccelerated(true);

	layout->addWidget(itersLabel, 0, 0);
	layout->addWidget(itersSpin, 0, 1);


	QLabel* incStepLabel = new QLabel("Incrementation step:");
	incStepSpin = new QSpinBox;
	incStepSpin->setRange(0, 500);
	incStepSpin->setValue(5);
	incStepSpin->setAccelerated(true);

	layout->addWidget(incStepLabel, 1, 0);
	layout->addWidget(incStepSpin, 1, 1);


	QLabel* decStepLabel = new QLabel("Decrementation step:");
	decStepSpin = new QSpinBox;
	decStepSpin->setRange(0, 500);
	decStepSpin->setValue(10);
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

void FaultFilterControl::activate()
{
  HAction* act = new HAction;
  act->setType(HAction::faultingFilter);
  act->setIterations(itersSpin->value());
  act->setIncStep(incStepSpin->value());
  act->setDecStep(decStepSpin->value());
  act->setWrap(wrapCheck->isChecked());
	emit activated(act);
}
