#include "dialog.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QIcon>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QFrame>
#include <QFont>
#include <QPainter>
#include <QTextEdit>

Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());						//ȥ��������
	this->setFixedSize(360, 160);

	initUI();
}

Dialog::~Dialog()
{

}

void Dialog::initUI()
{
	////��ʾ��Ϣ
	QFont font("Microsoft YaHei", 9, 50);
	QTextEdit* textLabelUp = new QTextEdit;
	textLabelUp->setText(QString::fromLocal8Bit("��⵽����ǰ�����汾���ͣ�Ϊ��֤�°湦��ʹ���ȶ�����������������"));

	textLabelUp->setFont(font);
	textLabelUp->setStyleSheet("background-color:#F0F0F0;color:black");
	textLabelUp->setFixedSize(280,50);
	textLabelUp->setEnabled(false);
	textLabelUp->setFrameShape(QFrame::NoFrame);

	//����ͼ��
	QLabel* iconLabel = new QLabel;
	iconLabel->setFixedSize(32, 32);
	QPixmap pixmap("./warning.png");
	iconLabel->setScaledContents(true);
	iconLabel->setPixmap(pixmap);

	QHBoxLayout *pHBLayout = new QHBoxLayout;
	pHBLayout->addStretch();
	pHBLayout->addWidget(iconLabel, Qt::AlignCenter);
	pHBLayout->addStretch();
	pHBLayout->addWidget(textLabelUp,Qt::AlignCenter);
	pHBLayout->addStretch();
	pHBLayout->setContentsMargins(10, 0, 10, 0);


	//���һ������
	QFrame* pFrameLine = new QFrame(this);
	pFrameLine->setFrameShape(QFrame::HLine);
	pFrameLine->setFixedSize(340, 2);
	//����ˮƽ����
	QHBoxLayout* pHBFrame = new QHBoxLayout;
	pFrameLine->setStyleSheet("border:1px solid #DFDDDD;");
	pHBFrame->addStretch();
	pHBFrame->addWidget(pFrameLine);
	pHBFrame->addStretch();

	//���һ��ȷ�ϰ�ť
	QPushButton* confirmBtn = new QPushButton(QString::fromLocal8Bit("ȷ��"));
	QFont btnfont("Microsoft YaHei", 8, 50);
	confirmBtn->setStyleSheet("QPushButton{border-radius:4px;background-color:#2C80E2;color:white}""QPushButton:hover{background-color:#3792FA;}");
	confirmBtn->setFont(btnfont);
	confirmBtn->setFixedSize(80, 28);
	

	//��ť��ˮƽ����
	QHBoxLayout *pHBLayoutBtn = new QHBoxLayout;
	pHBLayoutBtn->addStretch();
	pHBLayoutBtn->addWidget(confirmBtn);
	pHBLayoutBtn->setMargin(10);

	QVBoxLayout* pVBBtmLayout = new QVBoxLayout;
	pVBBtmLayout->addLayout(pHBFrame);
	pVBBtmLayout->addLayout(pHBLayoutBtn);

	//Dialog�ڲ���
	QVBoxLayout* pVBLayout = new QVBoxLayout;
	pVBLayout->addStretch();
	pVBLayout->addLayout(pHBLayout);
	pVBLayout->setSpacing(0);
	pVBLayout->addStretch();
	pVBLayout->addLayout(pVBBtmLayout);

	//��ӱ�����
	TitleBar * title = new TitleBar;

	//�ܲ���
	QVBoxLayout* pVBTotalLayout = new QVBoxLayout;
	pVBTotalLayout->addWidget(title);
	
	pVBTotalLayout->addLayout(pVBLayout);
	pVBTotalLayout->setMargin(0);
	pVBTotalLayout->setSpacing(0);

	connect(confirmBtn, &QPushButton::clicked, this, &Dialog::close);

	setLayout(pVBTotalLayout);

}

void Dialog::paintEvent(QPaintEvent * event)
{
	QPainter paint(this);
	paint.setRenderHint(QPainter::Antialiasing);

	QRectF outRect(0, 0, this->width(), this->height());//���γ���Ϊ���ڵĳ���
	QRectF inRect(1, 1, this->width() - 2, this->height() - 2);

	paint.setPen(Qt::NoPen);
	//�������
	paint.setBrush(QBrush(QColor(222,222,222)));
	paint.drawRect(outRect);
	//���ھ���
	paint.setBrush(QBrush(QColor(240,240,240)));
	paint.drawRect(inRect);
}

void Dialog::close()
{
	this->accept();
}


TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);	//ȥ��������										
	setFixedHeight(28);							//�̶��߶�
	initUI();
}

TitleBar::~TitleBar()
{

}

void TitleBar::initUI()
{
	//�رհ�ť
	closeButton* pCloseButton = new closeButton(this);
	pCloseButton->setFixedSize(30, 30);
	pCloseButton->setStyleSheet("QPushButton{border:none;background-color:#2C80E2;color:white}""QPushButton:hover{background-color:#3792FA;}");

	QIcon icon;
	icon.addFile(tr("./closeActive.png"));
	pCloseButton->setIcon(icon);

	//��ʾlabel
	QLabel* pTitleLabel = new QLabel;
	pTitleLabel->setContentsMargins(8, 0, 0, 0);
	QFont font("Microsoft YaHei", 7, 6);
	pTitleLabel->setText(QString::fromLocal8Bit("��ʾ"));
	pTitleLabel->setFont(font);
	pTitleLabel->setStyleSheet("background-color:#2C80E2;font-size:14px;color:white;text-align:center");

	QHBoxLayout *pHBLayout = new QHBoxLayout;
	pHBLayout->addWidget(pTitleLabel);
	pHBLayout->addStretch();
	pHBLayout->addWidget(pCloseButton);
	pHBLayout->setContentsMargins(0, 0, 0, 0);
	pHBLayout->setSpacing(0);

	QWidget *titleWidget = new QWidget;
	titleWidget->setLayout(pHBLayout);
	titleWidget->setStyleSheet("QWidget{background-color:#2C80E2;}");

	QHBoxLayout *mainWidgetLayout = new QHBoxLayout(this);
	mainWidgetLayout->addWidget(titleWidget);
	mainWidgetLayout->setMargin(0);

	connect(pCloseButton, &QPushButton::clicked, this, &TitleBar::onClicked);
	connect(pCloseButton, &closeButton::closeSignal, this, &TitleBar::closeBtMove);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
	m_bCloseBtMove = false;
	if (Qt::LeftButton == event->button())
	{
		m_pointClickPos = event->pos();
	}
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_bCloseBtMove && (event->buttons() & Qt::LeftButton))
	{
		QPoint relaPos(QCursor::pos() - m_pointClickPos);
		this->window()->move(relaPos);
	}
}

void TitleBar::onClicked()
{
	this->window()->close();
}

void TitleBar::closeBtMove()
{
	m_bCloseBtMove = true;
}


closeButton::closeButton(QWidget *parent)
	:QPushButton(parent)
{

}

 void closeButton::mouseMoveEvent(QMouseEvent *event)
 {
	 emit closeSignal();
 }
