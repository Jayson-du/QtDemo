#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
class QLabel;
class QPoint;

/*
*自定义窗体类
*/
class Dialog : public QDialog
{
	Q_OBJECT
public:
	Dialog(QWidget *parent = 0);
	~Dialog();

protected:
	void paintEvent(QPaintEvent* event);
private:
	void initUI();
	void close();
	bool m_isMove;
};

/*
*自定义标题栏类
*/
class TitleBar : public QWidget
{
	Q_OBJECT
public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();
protected:
	virtual void mousePressEvent(QMouseEvent *event);		//鼠标按下函数
	virtual void mouseMoveEvent(QMouseEvent *event);		//鼠标移动函数
	private slots:
	void onClicked();										// 进行关闭操作
	void closeBtMove();
private:
	void initUI();
	QPoint m_pointClickPos;
	bool m_bCloseBtMove = false;

};

class closeButton : public QPushButton
{
	Q_OBJECT
public:
	explicit closeButton(QWidget *parent = Q_NULLPTR);
signals:
	void closeSignal();
protected:
 	void mouseMoveEvent(QMouseEvent *event);
private:
	bool m_isClose;
};

#endif // DIALOG_H
