//#include "widget.h"

#include "operateXML.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
	operateXML xml;

	QString strFileName = "D:/10.xml";

	xml.writeXML(strFileName);
}
