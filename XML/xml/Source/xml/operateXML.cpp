#include "operateXML.hpp"
#include <QDomDocument>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

operateXML::operateXML()
{
}

operateXML::~operateXML()
{
}

void operateXML::writeXML(const QString & strFilePath)
{
	QFile file(strFilePath);

	//QIODevice::Truncate表示清空原来内容
	if (!file.open(QFile::ReadOnly | QFile::Truncate))
	{
		return;
	}

	//创建xml文档在内容中
	QDomDocument doc;
	//添加处理命令
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml", "version = \"1.0\" encoding=\"UTF-8\"");

	//创建注释
	QDomComment comment;
	comment = doc.createComment(QString::fromLocal8Bit("离开是为了更好的相聚"));
	QDomProcessingInstruction styleInstruction;
	styleInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/css\" href=\"style.css\"");
	doc.appendChild(instruction);	//文档开始声明

}

