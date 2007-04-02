#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "RandomFillControl.h"

RandomFillControl::RandomFillControl(QWidget* parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);


	QLabel* minLabel = new QLabel("Minimum:");
	minSpin = new QSpinBox;
	minSpin->setRange(-30000, 0);
	minSpin->setValue(-500);
	minSpin->setAccelerated(true);

	layout->addWidget(minLabel, 0, 0);
	layout->addWidget(minSpin, 0, 1);


	QLabel* maxLabel = new QLabel("Maximum:");
	maxSpin = new QSpinBox;
	maxSpin->setRange(0, 30000);
	maxSpin->setValue(500);
	maxSpin->setAccelerated(true);

	layout->addWidget(maxLabel, 1, 0);
	layout->addWidget(maxSpin, 1, 1);


	QPushButton* go = new QPushButton("&Go!");
	connect(go, SIGNAL(clicked()), this, SLOT(activate()));

	layout->addWidget(go, 2, 1);
}

void RandomFillControl::activate()
{
	emit activated(double(minSpin->value()), double(maxSpin->value()));
}
