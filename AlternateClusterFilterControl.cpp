#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "AlternateClusterFilterControl.h"
#include "HAction.h"

AlternateClusterFilterControl::AlternateClusterFilterControl(QWidget* parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);


	QLabel* radiusLabel = new QLabel("Diameter:");
	radiusSpin = new QSpinBox;
	radiusSpin->setRange(0, 20);
	radiusSpin->setValue(0);

	layout->addWidget(radiusLabel, 0, 0);
	layout->addWidget(radiusSpin, 0, 1);


	QPushButton* go = new QPushButton("&Go!");
	connect(go, SIGNAL(clicked()), this, SLOT(activate()));

	layout->addWidget(go, 1, 1);
}

void AlternateClusterFilterControl::activate()
{
  HAction* act = new HAction;
  act->setType(HAction::alternateClusterFilter);
  act->setRadius(radiusSpin->value());
	emit activated(act);
}
