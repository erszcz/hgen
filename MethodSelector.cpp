#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QGridLayout>
#include <QGroupBox>

#include "MethodSelector.h"

MethodSelector::MethodSelector(QWidget* parent)
	: QGroupBox(parent)
{
	setTitle("Transformation method:");
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	setMinimumWidth(230);
	setMaximumWidth(350);
	QGridLayout* layout = new QGridLayout(this);

	randomFillSel = new QRadioButton("Random fill", this);
	layout->addWidget(randomFillSel, 1, 0);
	connect(randomFillSel, SIGNAL(clicked()), this, SIGNAL(randomFillSelected()));
	
	clusterFillSel = new QRadioButton("Clustered fill", this);
	layout->addWidget(clusterFillSel, 2, 0);
	connect(clusterFillSel, SIGNAL(clicked()), this, SIGNAL(clusterFillSelected()));

	clusterFilterSel = new QRadioButton("Clustering filter", this);
	layout->addWidget(clusterFilterSel, 3, 0);
	connect(clusterFilterSel, SIGNAL(clicked()), this, SIGNAL(clusterFilterSelected()));

	alternateClusterFilterSel = new QRadioButton("Alternate clustering filter", this);
	layout->addWidget(alternateClusterFilterSel, 4, 0);
	connect(alternateClusterFilterSel, SIGNAL(clicked()), this, SIGNAL(alternateClusterFilterSelected()));

	liquidFilterSel = new QRadioButton("Fluid simulation", this);
	layout->addWidget(liquidFilterSel, 5, 0);
	connect(liquidFilterSel, SIGNAL(clicked()), this, SIGNAL(liquidFilterSelected()));

	smoothFilterSel = new QRadioButton("Smoothing", this);
	layout->addWidget(smoothFilterSel, 6, 0);
	connect(smoothFilterSel, SIGNAL(clicked()), this, SIGNAL(smoothFilterSelected()));

	walkerFilterSel = new QRadioButton("Random walkers", this);
	layout->addWidget(walkerFilterSel, 7, 0);
	connect(walkerFilterSel, SIGNAL(clicked()), this, SIGNAL(walkerFilterSelected()));

	faultFilterSel = new QRadioButton("Faulting", this);
	layout->addWidget(faultFilterSel, 8, 0);
	connect(faultFilterSel, SIGNAL(clicked()), this, SIGNAL(faultFilterSelected()));

	setEnabled(false);
}

bool MethodSelector::isEnabled() const
{
	return 
	randomFillSel->isEnabled() &&
	clusterFillSel->isEnabled() &&
	clusterFilterSel->isEnabled() &&
	alternateClusterFilterSel->isEnabled() &&
	liquidFilterSel->isEnabled() &&
	smoothFilterSel->isEnabled() &&
	walkerFilterSel->isEnabled() &&
	faultFilterSel->isEnabled();
}

void MethodSelector::setEnabled(bool flag)
{
	randomFillSel->setEnabled(flag);
	clusterFillSel->setEnabled(flag);
	clusterFilterSel->setEnabled(flag);
	alternateClusterFilterSel->setEnabled(flag);
	liquidFilterSel->setEnabled(flag);
	smoothFilterSel->setEnabled(flag);
	walkerFilterSel->setEnabled(flag);
	faultFilterSel->setEnabled(flag);
}
