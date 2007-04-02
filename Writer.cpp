#include <QObject>
#include <iostream>

#include "Writer.h"

using std::cout;
using std::cin;
using std::endl;

Writer::Writer(QObject* parent)
	: QObject(parent)
{}

void Writer::randomFill(double min, double max)
{
	cout << "min: " << min << "\tmax: " << max << endl;
}

void Writer::clusterFill(double min, double max, short clusterChance, short radius)
{
	cout << "min: " << min << "\tmax: " << max << "\tchance: "
	     << clusterChance << "\tradius: " << radius << endl;
}

void Writer::clusterFilter(short radius)
{
	cout << "radius: " << radius << endl;
}

void Writer::liquidFilter(double c, double d, double t, double u,
                          short iters, bool wrap)
{
	cout << "c: " << c << "\td: " << d << "\tt: " << t << "\tu: " << u
	     << "\titers: " << iters << "\twrap: " << wrap << endl;
}
