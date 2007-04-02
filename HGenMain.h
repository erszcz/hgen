#ifndef HGENMAIN_H
#define HGENMAIN_H

#include <QMainWindow>

class QMenu;
class QAction;

class ControlPanel;

class HGenMain : public QMainWindow
{
	Q_OBJECT

	public:
	HGenMain();

	private slots:
	void about();
	void usage();

	void statusReady();
	void statusProcessing();
	void statusMouse(int x, int y);

	private:
	void createActions();
	void createMenus();

	QAction* createMapAct;
	QAction* loadMapAct;
	QAction* saveMapAct;
	QAction* exitAct;
	QAction* aboutAct;
	QAction* aboutQtAct;
	QAction* usageAct;

	QMenu* fileMenu;
	QMenu* helpMenu;

	ControlPanel* panel;
};

#endif
