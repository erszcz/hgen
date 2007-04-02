#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

#include "CreateMapDialog.h"

CreateMapDialog::CreateMapDialog(QWidget* parent)
	: QDialog(parent)
{
	setWindowTitle("Create new heightmap");
	setFixedHeight(100);
	setMinimumWidth(250);
	QVBoxLayout* layout = new QVBoxLayout(this);
	QHBoxLayout* labels = new QHBoxLayout;
	QHBoxLayout* spins = new QHBoxLayout;
	QHBoxLayout* buttons = new QHBoxLayout;
	layout->addLayout(labels);
	layout->addLayout(spins);
	layout->addLayout(buttons);
	buttons->addStretch();

	widthLabel = new QLabel("Width:");
	labels->addWidget(widthLabel);
	widthSpin = new QSpinBox;
	widthSpin->setRange(0, 600);
	widthSpin->setValue(300);
	widthSpin->setAccelerated(true);
	spins->addWidget(widthSpin);

	heightLabel = new QLabel("Height:");
	labels->addWidget(heightLabel);
	heightSpin = new QSpinBox;
	heightSpin->setRange(0, 600);
	heightSpin->setValue(300);
	heightSpin->setAccelerated(true);
	spins->addWidget(heightSpin);

	marginLabel = new QLabel("Margin:");
	labels->addWidget(marginLabel);
	marginSpin = new QSpinBox;
	marginSpin->setRange(0, 20);
	marginSpin->setValue(2);
	spins->addWidget(marginSpin);

	accept = new QPushButton("Accept");
	buttons->addWidget(accept);
	connect(accept, SIGNAL(clicked()), this, SLOT(emitData()));

	cancel = new QPushButton("Cancel");
	buttons->addWidget(cancel);
	connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void CreateMapDialog::emitData()
{
	emit accepted(widthSpin->value(), heightSpin->value(), marginSpin->value());
	close();
}
