#include <QPainter>
#include "circlebutton.h"

CircleButton::CircleButton(QString text, QWidget* parent)
    : QPushButton(parent),
      m_isHover(false),
      m_isPressed(false)
{
    setFixedSize(120, 120);
}

CircleButton::~CircleButton()
{
}

void CircleButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor blue;

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

    QRectF rect = this->rect();
    painter.drawEllipse(rect);

    QPoint start(width() / 4, height() / 4);
    QPoint end(3 * width() / 4, 3 * height() / 4);
    QRectF textRect(start, end);

    painter.setPen(QPen(QColor(215, 219, 221)));
    QFont font("Times", 14);
    painter.setFont(font);

    painter.drawText(textRect, Qt::AlignCenter, tr("start"));
}

void CircleButton::enterEvent(QEvent* event)
{
    m_isHover = true;
    QPushButton::enterEvent(event);
}

void CircleButton::leaveEvent(QEvent* event)
{
    m_isHover = false;
    QPushButton::leaveEvent(event);
}

void CircleButton::mousePressEvent(QMouseEvent* event)
{
    m_isPressed = true;
    QPushButton::mousePressEvent(event);
    move(this->x(), this->y() + 5);
}

void CircleButton::mouseReleaseEvent(QMouseEvent* event)
{
    m_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
    move(this->x(), this->y() - 5);
}
