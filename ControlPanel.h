#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QMap>

class QVBoxLayout;
class QPushButton;
class QAction;

class MethodSelector;
class RandomFillControl;
class ClusterFillControl;
class ClusterFilterControl;
class AlternateClusterFilterControl;
class LiquidFilterControl;
class SmoothFilterControl;
class WalkerFilterControl;
class FaultFilterControl;

class MapPreview;
class Heightmap;

class ControlPanel : public QWidget
{
	Q_OBJECT

	public:
	ControlPanel(QWidget* parent = 0);
	~ControlPanel();

	QAction* createMapAct;
	QAction* loadMapAct;
	QAction* saveMapAct;

	private slots:
	void showRandomFillControl();
	void showClusterFillControl();
	void showClusterFilterControl();
	void showAlternateClusterFilterControl();
	void showLiquidFilterControl();
	void showSmoothFilterControl();
	void showWalkerFilterControl();
	void showFaultFilterControl();

	void createMap();
	void loadMap();
	void saveMap();
	// temp; nalezy to zastapic klasa MapManager z odpowiednimi slotami.
	// ma on sie tez zajmowac czasem i losowymi, niepowtarzalnymi nazwami
	// inicjalizowanych instancji, udostepniac sloty do zmieniania aktualnej mapy, itd
	void initNewMap(int width, int height, int margin);
	signals:
	void processingStarted();
	void processingFinished();
	// fin
	
	// tez temp
	void mouseAt(int, int);
	// fin

	private:
	void         createMainLayout();
	void         createActions();
	QVBoxLayout* createControlsColumn();
	void         createConnections();

	QPushButton* create;
	QPushButton* load;
	QPushButton* save;

	MethodSelector*       methodSelector;
	RandomFillControl*    randomFillControl;
	ClusterFillControl*   clusterFillControl;
	ClusterFilterControl* clusterFilterControl;
	AlternateClusterFilterControl* alternateClusterFilterControl;
	LiquidFilterControl*  liquidFilterControl;
	SmoothFilterControl*  smoothFilterControl;
	WalkerFilterControl*  walkerFilterControl;
	FaultFilterControl*   faultFilterControl;

	MapPreview* preview;

	QMap<QString, Heightmap*>* manager;
};

#endif
