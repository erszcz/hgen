#ifndef METHODSELECTOR_H
#define METHODSELECTOR_H

#include <QGroupBox>

class QWidget;
class QRadioButton;

class MethodSelector : public QGroupBox
{
	Q_OBJECT

	public:
	MethodSelector(QWidget* parent = 0);

	public slots:
	bool isEnabled() const;
	void setEnabled(bool flag);

	signals:
	void randomFillSelected();
	void clusterFillSelected();
	void clusterFilterSelected();
	void alternateClusterFilterSelected();
	void liquidFilterSelected();
	void smoothFilterSelected();
	void walkerFilterSelected();
	void faultFilterSelected();

	private:
	QRadioButton* randomFillSel;
	QRadioButton* clusterFillSel;
	QRadioButton* clusterFilterSel;
	QRadioButton* alternateClusterFilterSel;
	QRadioButton* liquidFilterSel;
	QRadioButton* smoothFilterSel;
	QRadioButton* walkerFilterSel;
	QRadioButton* faultFilterSel;
};

#endif
