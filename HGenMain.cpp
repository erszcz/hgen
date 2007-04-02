#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>

#include "HGenMain.h"
#include "ControlPanel.h"

HGenMain::HGenMain()
	: QMainWindow()
{
	panel = new ControlPanel;
	setCentralWidget(panel);

	createActions();
	createMenus();

	setWindowTitle("HGen");

	connect(panel, SIGNAL(processingFinished()), this, SLOT(statusReady()));
	connect(panel, SIGNAL(processingStarted()), this, SLOT(statusProcessing()));
	statusReady();

	connect(panel, SIGNAL(mouseAt(int, int)), this, SLOT(statusMouse(int, int)));
}

void HGenMain::about()
{
	QMessageBox::information(this, tr("About HGen"),
	                tr("<p>This program was written by Radoslaw Szymczyszyn in 2006/2007 as a school project for IT lessons.</p><p>One is free to use it without limits. However, the author would like to know about any modifications to the source.</p><p>Contact info:<br />Radoslaw Szymczyszyn<br />e-mail: lavrin@gmail.com<br />Jabber ID: lavrin@underley.eu.org</p>"));
}

void HGenMain::usage()
{
	QMessageBox::information(this, tr("HGen usage"),
	                tr("<h1>HGen quick start guide</h1>\
									<p>The user interface was designed to be pretty self-explanatory, \
									but here is a quick overview of it.</p><p>The menu bar is made up \
									of two menus: one consists of options also available from the UI \
									(i.e. New, Load, Save) and Exit and the other one contains \
									information about the program.</p><p>Just after starting the \
									application two options are available to the user: New and Load.<br />\
									Selecting New will result in an input dialog being displayed on the \
									screen waiting for supplying some information. Width an height are \
									self-explanatory. Margin is the width of a zone around the heightmap \
									which is never visible to the user, but used for internal operations. \
									The higher its value, the longer it takes to do some transformations. \
									In this release it is limited to 20. The default will do just fine.\
									<br />Selecting Load will allow the user to select a previously \
									created PNG (Portable Network Graphics) image from the drive in order \
									to further process it.<br />After either creating a new heightmap or \
									loading an existing one the other options are enabled, i.e. Save and \
									all the transformation methods. Selecting one of the methods will \
									result in its adjustable properties being displayed in the lower left \
									part of the window. Having fine-tuned these settings, the user has \
									got not much more to do than to press the Go button. Processing is \
									indicatesd by both the state of the cursor as well as a proper text \
									in the status bar. Save allows the user to store the displayed image \
									on his/her drive.</p><p>While hovering over the image the status bar \
									displays current position of the cursor (X coordinate, Y coordinate)\
									relative to the top left corner of the image.</p>\
									<p>At last, but not least, an important thing to say is that the \
									user takes all the responsibility for the final result of all the \
									transformations - by that I mean that the outcome may not look even \
									close to a useful heightmap ;)</p>"));
}

void HGenMain::statusReady()
{
	statusBar()->showMessage("Ready", 2000);
	QApplication::restoreOverrideCursor();
}

void HGenMain::statusProcessing()
{
	statusBar()->showMessage("Processing...");
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
}

void HGenMain::statusMouse(int x, int y)
{
	if(x != -1 && y != -1)
		statusBar()->showMessage(QString::number(x) += QString(", ") += QString::number(y));
	else
		statusBar()->showMessage("");
}

void HGenMain::createActions()
{
	createMapAct = panel->createMapAct;
	loadMapAct = panel->loadMapAct;
	saveMapAct = panel->saveMapAct;

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+X"));
	connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setShortcut(tr("Ctrl+A"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About Qt"), this);
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	usageAct = new QAction(tr("&Usage"), this);
	usageAct->setShortcut(tr("Ctrl+U"));
	connect(usageAct, SIGNAL(triggered()), this, SLOT(usage()));
}

void HGenMain::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(createMapAct);
	fileMenu->addAction(loadMapAct);
	fileMenu->addAction(saveMapAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
	helpMenu->addAction(usageAct);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(helpMenu);
}
