#ifndef CREATEMAPDIALOG_H
#define CREATEMAPDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QSpinBox;
class QPushButton;

class CreateMapDialog : public QDialog
{
	Q_OBJECT

	public:
	CreateMapDialog(QWidget* parent = 0);

	private slots:
	void emitData();

	signals:
	void accepted(int width, int height, int margin);

	private:
	QLabel* nameLabel;
	QLineEdit* nameEdit;
	QLabel* widthLabel;
	QSpinBox* widthSpin;
	QLabel* heightLabel;
	QSpinBox* heightSpin;
	QLabel* marginLabel;
	QSpinBox* marginSpin;

	QPushButton* accept;
	QPushButton* cancel;
};

#endif
