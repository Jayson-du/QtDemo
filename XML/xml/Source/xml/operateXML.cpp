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
	if (!file.open(QFile::WriteOnly | QFile::Truncate))
	{
		return;
	}

	//����xml�ĵ����ڴ���
	QDomDocument doc;
	//��Ӵ�������
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	//����ע��
	QDomComment comment;
	comment = doc.createComment(QString::fromLocal8Bit("�뿪��Ϊ�˸��õĹ���"));
	QDomProcessingInstruction styleInstruction;
	styleInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/css\" href=\"style.css\"");
	doc.appendChild(instruction); //�ĵ���ʼ����
	doc.appendChild(comment);
	doc.appendChild(styleInstruction);  // ����ָ��

	//��Ӹ��ڵ�
	QDomElement root = doc.createElement("library");
	root.setAttribute("Version", "2.1");
	doc.appendChild(root);
	//��ӵ�һ���ӽڵ㼰����Ԫ��
	QDomElement book = doc.createElement("book");
	//��ʽһ����������  ���м�ֵ�Ե�ֵ�����Ǹ�������
	book.setAttribute("id", 1);
	//��ʽ������������ ֵ�������ַ���
	QDomAttr time = doc.createAttribute("time");
	time.setValue("2013/6/13");
	book.setAttributeNode(time);
	QDomElement title = doc.createElement("title"); //������Ԫ��
	QDomText text; //�������ű�ǩ�м��ֵ
	text = doc.createTextNode("C++ primer");
	book.appendChild(title);
	title.appendChild(text);
	QDomElement author = doc.createElement("author"); //������Ԫ��
	text = doc.createTextNode("Stanley Lippman");
	author.appendChild(text);
	book.appendChild(author);
	//��ӽڵ�book��Ϊ���ڵ���ӽڵ�
	root.appendChild(book);

	//��ӵڶ����ӽڵ㼰����Ԫ��
	book = doc.createElement("book");
	book.setAttribute("id", 2);
	time = doc.createAttribute("time");
	time.setValue("2007/5/25");
	book.setAttributeNode(time);
	title = doc.createElement("title");
	text = doc.createTextNode("Thinking in Java");
	book.appendChild(title);
	title.appendChild(text);

	author = doc.createElement("author");
	text = doc.createTextNode("Bruce Eckel");
	author.appendChild(text);
	book.appendChild(author);
	
	//����ӽڵ���ӽڵ�
	QDomElement nation = doc.createElement("nation");	
	QDomElement position = doc.createElement("position");
	text = doc.createTextNode("XiAn");
	position.appendChild(text);
	nation.appendChild(position);
	book.appendChild(nation);
	root.appendChild(book);

	//������ļ�
	QTextStream out_stream(&file);
	doc.save(out_stream, 4);					//����4��
	file.close();
}


