#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QPainterPath>
#include <QDebug>
#include "verticalbutton.h"

#define EXTENDLEN   5

VerticalButton::VerticalButton(QString text, bool rotated, QWidget* parent)
    : QPushButton(parent),
      m_text(text),
      m_isRotated(rotated),
      m_isHover(false),
      m_isPressed(false)
{
    setFixedSize(40, 140);
}

VerticalButton::~VerticalButton()
{
}

void VerticalButton::paintEvent(QPaintEvent* event)
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
    }
    else {
        blue.setRgb(53, 152, 219);
    }

    if (m_isPressed) {
        blue.setRgb(46, 134, 193);
    }

    QBrush brush(blue);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);

    QRectF rectf = this->rect();

    QPointF pointStart(0, 3 * height() / 4);
    QPointF pointBottom(width() / 2, height());
    QPointF pointTop(width() / 2, 0);
    QPointF pointEnd(0, height() / 4);
    QPointF littleRectStart(-width() / 4, height() / 4);
    QPointF littleRectEnd(width() / 4, 3 * height() / 4);
    QRectF littleRect(littleRectStart, littleRectEnd);


    QPainterPath path;
    path.moveTo(pointStart);
    path.lineTo(pointBottom);
    path.arcTo(rectf, -90.0f, 180.0f);
    path.lineTo(pointEnd);
    path.moveTo(0, height() / 2);
    path.arcTo(littleRect, 90.0f, -180.0f);
    painter.drawPath(path);

    if (m_isRotated) {
        painter.translate(width() / 2, height() / 2);
        painter.rotate(90);
        painter.translate(-width() / 2, -height() / 2);
    }
    else {
        painter.translate(width() / 2, height() / 2);
        painter.rotate(90);
        painter.translate(-width() / 2, -height() / 2);
    }

    QPointF start(rectf.topLeft().x() - EXTENDLEN, rectf.topLeft().y() - EXTENDLEN);
    QPointF end(rectf.bottomRight().x() + EXTENDLEN, rectf.bottomRight().y() + EXTENDLEN);

    QRectF textRect(start, end);

    painter.setPen(QPen(QColor(215, 219, 221)));
    QFont font("Times", 14);
    painter.setFont(font);

    painter.drawText(textRect, Qt::AlignCenter, m_text);
}

void VerticalButton::enterEvent(QEvent* event)
{
    m_isHover = true;
    QPushButton::enterEvent(event);
}

void VerticalButton::leaveEvent(QEvent* event)
{
    m_isHover = false;
    QPushButton::leaveEvent(event);
}

void VerticalButton::mousePressEvent(QMouseEvent* event)
{
    m_isPressed = true;
    QPushButton::mousePressEvent(event);
    move(this->x(), this->y() + 5);
}

void VerticalButton::mouseReleaseEvent(QMouseEvent* event)
{
    m_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
    move(this->x(), this->y() - 5);
}
