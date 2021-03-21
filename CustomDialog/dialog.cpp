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
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());						//去掉标题栏
	this->setFixedSize(360, 160);

	initUI();
}

Dialog::~Dialog()
{

}

void Dialog::initUI()
{
	////提示信息
	QFont font("Microsoft YaHei", 9, 50);
	QTextEdit* textLabelUp = new QTextEdit;
	textLabelUp->setText(QString::fromLocal8Bit("检测到您当前驱动版本过低，为保证新版功能使用稳定，请先升级驱动。"));

	textLabelUp->setFont(font);
	textLabelUp->setStyleSheet("background-color:#F0F0F0;color:black");
	textLabelUp->setFixedSize(280,50);
	textLabelUp->setEnabled(false);
	textLabelUp->setFrameShape(QFrame::NoFrame);

	//设置图标
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


	//添加一个横线
	QFrame* pFrameLine = new QFrame(this);
	pFrameLine->setFrameShape(QFrame::HLine);
	pFrameLine->setFixedSize(340, 2);
	//横线水平布局
	QHBoxLayout* pHBFrame = new QHBoxLayout;
	pFrameLine->setStyleSheet("border:1px solid #DFDDDD;");
	pHBFrame->addStretch();
	pHBFrame->addWidget(pFrameLine);
	pHBFrame->addStretch();

	//添加一个确认按钮
	QPushButton* confirmBtn = new QPushButton(QString::fromLocal8Bit("确认"));
	QFont btnfont("Microsoft YaHei", 8, 50);
	confirmBtn->setStyleSheet("QPushButton{border-radius:4px;background-color:#2C80E2;color:white}""QPushButton:hover{background-color:#3792FA;}");
	confirmBtn->setFont(btnfont);
	confirmBtn->setFixedSize(80, 28);
	

	//按钮的水平布局
	QHBoxLayout *pHBLayoutBtn = new QHBoxLayout;
	pHBLayoutBtn->addStretch();
	pHBLayoutBtn->addWidget(confirmBtn);
	pHBLayoutBtn->setMargin(10);

	QVBoxLayout* pVBBtmLayout = new QVBoxLayout;
	pVBBtmLayout->addLayout(pHBFrame);
	pVBBtmLayout->addLayout(pHBLayoutBtn);

	//Dialog内布局
	QVBoxLayout* pVBLayout = new QVBoxLayout;
	pVBLayout->addStretch();
	pVBLayout->addLayout(pHBLayout);
	pVBLayout->setSpacing(0);
	pVBLayout->addStretch();
	pVBLayout->addLayout(pVBBtmLayout);

	//添加标题栏
	TitleBar * title = new TitleBar;

	//总布局
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

	QRectF outRect(0, 0, this->width(), this->height());//矩形长宽为窗口的长宽
	QRectF inRect(1, 1, this->width() - 2, this->height() - 2);

	paint.setPen(Qt::NoPen);
	//画外矩形
	paint.setBrush(QBrush(QColor(222,222,222)));
	paint.drawRect(outRect);
	//画内矩形
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
	setWindowFlags(Qt::FramelessWindowHint);	//去掉标题栏										
	setFixedHeight(28);							//固定高度
	initUI();
}

TitleBar::~TitleBar()
{

}

void TitleBar::initUI()
{
	//关闭按钮
	closeButton* pCloseButton = new closeButton(this);
	pCloseButton->setFixedSize(30, 30);
	pCloseButton->setStyleSheet("QPushButton{border:none;background-color:#2C80E2;color:white}""QPushButton:hover{background-color:#3792FA;}");

	QIcon icon;
	icon.addFile(tr("./closeActive.png"));
	pCloseButton->setIcon(icon);

	//提示label
	QLabel* pTitleLabel = new QLabel;
	pTitleLabel->setContentsMargins(8, 0, 0, 0);
	QFont font("Microsoft YaHei", 7, 6);
	pTitleLabel->setText(QString::fromLocal8Bit("提示"));
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
