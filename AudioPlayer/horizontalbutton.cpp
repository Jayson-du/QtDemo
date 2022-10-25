#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QPainterPath>
#include <QDebug>
#include "horizontalbutton.h"

HorizontalButton::HorizontalButton(QString text, bool rotated, QWidget* parent)
    : QPushButton(parent),
      m_text(text),
      m_isRotated(rotated),
      m_isHover(false),
      m_isPressed(false)
{
    setFixedSize(140, 40);
}

HorizontalButton::~HorizontalButton()
{
}

void HorizontalButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor blue;

    if (m_isRotated) {
        painter.translate(width() / 2, height() / 2);
        painter.rotate(180);
        painter.translate(-width() / 2, -height() / 2);
    }
	
    if (m_isHover) {
        blue.setRgb(93, 173, 226);
    } else {
        blue.setRgb(53, 152, 219);
    }

    if (m_isPressed) {
        blue.setRgb(46, 134, 193);
    }

    QBrush brush(blue);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);


    QRectF rect = this->rect();

    QPoint pointStart(width() - (width() / 4), height());
    QPoint pointRight(width(), height() / 2);
    QPoint pointleft(0, height() / 2);
    QPoint pointEnd(width() / 4, height());
    
    QPointF littleRectStart(width() / 4, 3 * height() / 4);
    QPointF littleRectEnd(3 * width() / 4, 5 * height() / 4);
    QRectF littleRect(littleRectStart, littleRectEnd);
    

    QPainterPath path;
    path.moveTo(pointStart);       
    path.lineTo(pointRight);       
    path.arcTo(rect, 0.0f, 180.0f);
    path.lineTo(pointEnd);
    path.moveTo(width() / 2, height());
    path.arcTo(littleRect, 0.0f, 180.0f);
    painter.drawPath(path);
    
    painter.resetTransform();
    QPoint start(width() / 4, height() / 4);
    QPoint end(3 * width() / 4, 3 * height() / 4);
    QRectF textRect(start, end);
    
    painter.setPen(QPen(QColor(215, 219, 221)));
    QFont font("Times", 14);
    painter.setFont(font);
    
    painter.drawText(textRect, Qt::AlignCenter, m_text);
}

void HorizontalButton::enterEvent(QEvent *event)
{
    m_isHover = true;
    QPushButton::enterEvent(event);
}

void HorizontalButton::leaveEvent(QEvent *event)
{
    m_isHover = false;
    QPushButton::leaveEvent(event);

}

void HorizontalButton::mousePressEvent(QMouseEvent *event)
{
    m_isPressed = true;
    QPushButton::mousePressEvent(event);
    move(this->x(), this->y() + 5);
}

void HorizontalButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
    move(this->x(), this->y() - 5);
}

//QSize MPushButton::getTextSize(const QString& text)
//{
//	/* 设置字体属性 */
//	QFont font;
//	font.setPixelSize(16);
//
//	/* 设置字体信息 */
//	QFontMetrics metrics(font);
//
//	return metrics.boundingRect(text).size();
//}
