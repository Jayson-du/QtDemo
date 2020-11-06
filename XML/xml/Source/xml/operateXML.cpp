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
	if (!file.open(QFile::WriteOnly | QFile::Truncate))
	{
		return;
	}

	//创建xml文档在内存中
	QDomDocument doc;
	//添加处理命令
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	//创建注释
	QDomComment comment;
	comment = doc.createComment(QString::fromLocal8Bit("离开是为了更好的归来"));
	QDomProcessingInstruction styleInstruction;
	styleInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/css\" href=\"style.css\"");
	doc.appendChild(instruction); //文档开始声明
	doc.appendChild(comment);
	doc.appendChild(styleInstruction);  // 处理指令

	//添加根节点
	QDomElement root = doc.createElement("library");
	root.setAttribute("Version", "2.1");
	doc.appendChild(root);
	//添加第一个子节点及其子元素
	QDomElement book = doc.createElement("book");
	//方式一：创建属性  其中键值对的值可以是各种类型
	book.setAttribute("id", 1);
	//方式二：创建属性 值必须是字符串
	QDomAttr time = doc.createAttribute("time");
	time.setValue("2013/6/13");
	book.setAttributeNode(time);
	QDomElement title = doc.createElement("title"); //创建子元素
	QDomText text; //设置括号标签中间的值
	text = doc.createTextNode("C++ primer");
	book.appendChild(title);
	title.appendChild(text);
	QDomElement author = doc.createElement("author"); //创建子元素
	text = doc.createTextNode("Stanley Lippman");
	author.appendChild(text);
	book.appendChild(author);
	//添加节点book做为根节点的子节点
	root.appendChild(book);

	//添加第二个子节点及其子元素
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
	
	//添加子节点的子节点
	QDomElement nation = doc.createElement("nation");	
	QDomElement position = doc.createElement("position");
	text = doc.createTextNode("XiAn");
	position.appendChild(text);
	nation.appendChild(position);
	book.appendChild(nation);
	root.appendChild(book);

	//输出到文件
	QTextStream out_stream(&file);
	doc.save(out_stream, 4);					//缩进4格
	file.close();
}


