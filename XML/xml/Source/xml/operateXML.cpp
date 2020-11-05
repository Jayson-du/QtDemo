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

	//QIODevice::Truncate��ʾ���ԭ������
	if (!file.open(QFile::ReadOnly | QFile::Truncate))
	{
		return;
	}

	//����xml�ĵ���������
	QDomDocument doc;
	//��Ӵ�������
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml", "version = \"1.0\" encoding=\"UTF-8\"");

	//����ע��
	QDomComment comment;
	comment = doc.createComment(QString::fromLocal8Bit("�뿪��Ϊ�˸��õ����"));
	QDomProcessingInstruction styleInstruction;
	styleInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/css\" href=\"style.css\"");
	doc.appendChild(instruction);	//�ĵ���ʼ����

}

