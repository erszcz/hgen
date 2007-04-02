#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "ClusterFillControl.h"

ClusterFillControl::ClusterFillControl(QWidget* parent)
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


	QLabel* chanceLabel = new QLabel("Clustering chance:");
	chanceSpin = new QSpinBox;
	chanceSpin->setRange(0, 100);
	chanceSpin->setValue(60);
	chanceSpin->setAccelerated(true);

	layout->addWidget(chanceLabel, 2, 0);
	layout->addWidget(chanceSpin, 2, 1);


	QLabel* radiusLabel = new QLabel("Radius:");
	radiusSpin = new QSpinBox;
	radiusSpin->setRange(0, 20);
	radiusSpin->setValue(2);

	layout->addWidget(radiusLabel, 3, 0);
	layout->addWidget(radiusSpin, 3, 1);


	QPushButton* go = new QPushButton("&Go!");
	connect(go, SIGNAL(clicked()), this, SLOT(activate()));

	layout->addWidget(go, 4, 1);
}

void ClusterFillControl::activate()
{
	emit activated(double(minSpin->value()), double(maxSpin->value()),
	               chanceSpin->value(), radiusSpin->value());
}
