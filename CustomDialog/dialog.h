#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
class QLabel;
class QPoint;

/*
*�Զ��崰����
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
*�Զ����������
*/
class TitleBar : public QWidget
{
	Q_OBJECT
public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();
protected:
	virtual void mousePressEvent(QMouseEvent *event);		//��갴�º���
	virtual void mouseMoveEvent(QMouseEvent *event);		//����ƶ�����
	private slots:
	void onClicked();										// ���йرղ���
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
