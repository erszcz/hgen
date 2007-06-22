#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMap>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QAction>

#include <vector>

#include "ControlPanel.h"
#include "MapControls.h"
#include "HAction.h"

#include "ScrollMapPreview.h"
#include "CreateMapDialog.h"

using std::vector;

ControlPanel::ControlPanel(QWidget* parent)
	: QWidget(parent)
{
	preview = new ScrollMapPreview;
	manager = new QMap<QString, Heightmap*>;

	createMainLayout();
	createActions();
	createConnections();
}

void ControlPanel::createMainLayout()
{
	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainLayout->addLayout(createControlsColumn());
	mainLayout->addStretch();
	QVBoxLayout* previewLayout = new QVBoxLayout;
	previewLayout->addWidget(preview);
	previewLayout->addStretch();
	mainLayout->addLayout(previewLayout);
}

QVBoxLayout* ControlPanel::createControlsColumn()
{
	QVBoxLayout* layout = new QVBoxLayout;

	QHBoxLayout* buttons = new QHBoxLayout;
	create = new QPushButton("&New");
	buttons->addWidget(create);
	load = new QPushButton("&Load");
	buttons->addWidget(load);
	save = new QPushButton("&Save");
	save->setEnabled(false);
	buttons->addWidget(save);
	layout->addLayout(buttons);
	
	methodSelector = new MethodSelector;
	layout->addWidget(methodSelector);

	randomFillControl = new RandomFillControl;
	layout->addWidget(randomFillControl);
	randomFillControl->hide();

	clusterFillControl = new ClusterFillControl;
	layout->addWidget(clusterFillControl);
	clusterFillControl->hide();

	clusterFilterControl = new ClusterFilterControl;
	layout->addWidget(clusterFilterControl);
	clusterFilterControl->hide();

	alternateClusterFilterControl = new AlternateClusterFilterControl;
	layout->addWidget(alternateClusterFilterControl);
	alternateClusterFilterControl->hide();

	liquidFilterControl = new LiquidFilterControl;
	layout->addWidget(liquidFilterControl);
	liquidFilterControl->hide();

	smoothFilterControl = new SmoothFilterControl;
	layout->addWidget(smoothFilterControl);
	smoothFilterControl->hide();

	walkerFilterControl = new WalkerFilterControl;
	layout->addWidget(walkerFilterControl);
	walkerFilterControl->hide();

	faultFilterControl = new FaultFilterControl;
	layout->addWidget(faultFilterControl);
	faultFilterControl->hide();

	layout->addStretch();
	
	return layout;
}

void ControlPanel::createConnections()
{
	// buttons
	connect(create, SIGNAL(clicked()), createMapAct, SIGNAL(triggered()));
	connect(load, SIGNAL(clicked()), loadMapAct, SIGNAL(triggered()));
	connect(save, SIGNAL(clicked()), saveMapAct, SIGNAL(triggered()));


	connect(methodSelector, SIGNAL(randomFillSelected()),
	        this, SLOT(showRandomFillControl()));
	connect(methodSelector, SIGNAL(clusterFillSelected()),
	        this, SLOT(showClusterFillControl()));
	connect(methodSelector, SIGNAL(clusterFilterSelected()),
	        this, SLOT(showClusterFilterControl()));
	connect(methodSelector, SIGNAL(alternateClusterFilterSelected()),
	        this, SLOT(showAlternateClusterFilterControl()));
	connect(methodSelector, SIGNAL(liquidFilterSelected()),
	        this, SLOT(showLiquidFilterControl()));
	connect(methodSelector, SIGNAL(smoothFilterSelected()),
	        this, SLOT(showSmoothFilterControl()));
	connect(methodSelector, SIGNAL(walkerFilterSelected()),
	        this, SLOT(showWalkerFilterControl()));
	connect(methodSelector, SIGNAL(faultFilterSelected()),
	        this, SLOT(showFaultFilterControl()));

	//temp
	connect(preview, SIGNAL(mouseAt(int, int)), this, SIGNAL(mouseAt(int, int)));
}

void ControlPanel::createActions()
{
	createMapAct = new QAction(tr("New"), this);
	createMapAct->setShortcut(tr("Ctrl+N"));
	connect(createMapAct, SIGNAL(triggered()), this, SLOT(createMap()));
	
	loadMapAct = new QAction(tr("Load"), this);
	loadMapAct->setShortcut(tr("Ctrl+L"));
	connect(loadMapAct, SIGNAL(triggered()), this, SLOT(loadMap()));

	saveMapAct = new QAction(tr("Save"), this);
	saveMapAct->setShortcut(tr("Ctrl+S"));
	connect(saveMapAct, SIGNAL(triggered()), this, SLOT(saveMap()));
	saveMapAct->setEnabled(false);
}

void ControlPanel::showRandomFillControl()
{
	clusterFillControl->hide();
	clusterFilterControl->hide();
	alternateClusterFilterControl->hide();
	liquidFilterControl->hide();
	smoothFilterControl->hide();
	walkerFilterControl->hide();
	faultFilterControl->hide();

	randomFillControl->show();
}

void ControlPanel::showClusterFillControl()
{
	randomFillControl->hide();
	clusterFilterControl->hide();
	alternateClusterFilterControl->hide();
	liquidFilterControl->hide();
	smoothFilterControl->hide();
	walkerFilterControl->hide();
	faultFilterControl->hide();

	clusterFillControl->show();
}

void ControlPanel::showClusterFilterControl()
{
	randomFillControl->hide();
	clusterFillControl->hide();
	alternateClusterFilterControl->hide();
	liquidFilterControl->hide();
	smoothFilterControl->hide();
	walkerFilterControl->hide();
	faultFilterControl->hide();

	clusterFilterControl->show();
}

void ControlPanel::showAlternateClusterFilterControl()
{
	randomFillControl->hide();
	clusterFillControl->hide();
	clusterFilterControl->hide();
	liquidFilterControl->hide();
	smoothFilterControl->hide();
	walkerFilterControl->hide();
	faultFilterControl->hide();

  alternateClusterFilterControl->show();
}

void ControlPanel::showLiquidFilterControl()
{
	randomFillControl->hide();
	clusterFillControl->hide();
	clusterFilterControl->hide();
	alternateClusterFilterControl->hide();
	smoothFilterControl->hide();
	walkerFilterControl->hide();
	faultFilterControl->hide();

	liquidFilterControl->show();
}

void ControlPanel::showSmoothFilterControl()
{
	randomFillControl->hide();
	clusterFillControl->hide();
	clusterFilterControl->hide();
	alternateClusterFilterControl->hide();
	liquidFilterControl->hide();
	walkerFilterControl->hide();
	faultFilterControl->hide();

	smoothFilterControl->show();
}

void ControlPanel::showWalkerFilterControl()
{
	randomFillControl->hide();
	clusterFillControl->hide();
	clusterFilterControl->hide();
	alternateClusterFilterControl->hide();
	liquidFilterControl->hide();
	smoothFilterControl->hide();
	faultFilterControl->hide();

	walkerFilterControl->show();
}

void ControlPanel::showFaultFilterControl()
{
	randomFillControl->hide();
	clusterFillControl->hide();
	clusterFilterControl->hide();
	alternateClusterFilterControl->hide();
	liquidFilterControl->hide();
	smoothFilterControl->hide();
	walkerFilterControl->hide();

	faultFilterControl->show();

}

void ControlPanel::createMap()
{
	CreateMapDialog d(this);
	connect(&d, SIGNAL(accepted(int, int, int)),
	        this, SLOT(initNewMap(int, int, int)));
	d.exec();
}

void ControlPanel::loadMap()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load existing map",
	                                                QDir::currentPath(), "*.png");
	if(!filename.isEmpty())
	{
		QImage temp(filename);
		if (!temp.isNull())
		{
			short margin = QInputDialog::getInteger(this, "Load existing map",
					"Please supply map margin (used for internal operations)",
					2, 0, 20);

			QImage temp(filename);
			manager->insert("current", new Heightmap(filename, temp.width(),
						temp.height(), margin));
			preview->setMap(manager->value("current"));

      vector<QWidget*> controls;
      controls.push_back(randomFillControl);
      controls.push_back(clusterFillControl);
      controls.push_back(clusterFilterControl);
      controls.push_back(alternateClusterFilterControl);
      controls.push_back(liquidFilterControl);
      controls.push_back(smoothFilterControl);
      controls.push_back(walkerFilterControl);
      controls.push_back(faultFilterControl);
      for (int i = 0; i < controls.size(); ++i)
        connect(controls[i], SIGNAL(activated(HAction*)),
                manager->value("current"), SLOT(performHAction(HAction*)));

			connect(manager->value("current"), SIGNAL(processingStarted()), this, SIGNAL(processingStarted()));
			connect(manager->value("current"), SIGNAL(processingFinished()), this, SIGNAL(processingFinished()));

			save->setEnabled(true);
			saveMapAct->setEnabled(true);
			methodSelector->setEnabled(true);
		}
		else
		{
			QMessageBox::critical(this, "Error loading map",
					tr("Could not load file."));
		}
	}
}

void ControlPanel::saveMap()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save current map",
	                                                QDir::currentPath(), "*.png");
	if(fileName.isEmpty())
		return;
	if(! manager->value("current")->saveToDisk(fileName += ".png") )
		QMessageBox::critical(this, "Error saving to disk",
		                      tr("File %1 could not be written.").arg(fileName));
}

void ControlPanel::initNewMap(int width, int height, int margin)
{
	manager->insert("current", new Heightmap(width, height, margin));

	preview->setMap(manager->value("current"));

  vector<QWidget*> controls;
  controls.push_back(randomFillControl);
  controls.push_back(clusterFillControl);
  controls.push_back(clusterFilterControl);
  controls.push_back(alternateClusterFilterControl);
  controls.push_back(liquidFilterControl);
  controls.push_back(smoothFilterControl);
  controls.push_back(walkerFilterControl);
  controls.push_back(faultFilterControl);
  for (int i = 0; i < controls.size(); ++i)
    connect(controls[i], SIGNAL(activated(HAction*)),
            manager->value("current"), SLOT(performHAction(HAction*)));

	connect(manager->value("current"), SIGNAL(processingStarted()), this, SIGNAL(processingStarted()));
	connect(manager->value("current"), SIGNAL(processingFinished()), this, SIGNAL(processingFinished()));

	save->setEnabled(true);
	saveMapAct->setEnabled(true);
	methodSelector->setEnabled(true);
}

ControlPanel::~ControlPanel()
{
	QList<QString> keys = manager->uniqueKeys();
	while(!keys.isEmpty())
	{
		QString currentKey = keys.takeFirst();
		delete manager->take(currentKey);
	}
	if(!manager->isEmpty())
		manager->clear();
	delete manager;
}
