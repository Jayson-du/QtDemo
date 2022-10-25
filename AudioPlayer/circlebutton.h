#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QPushButton>
#include <QLineEdit>

#define PAINT

class CircleButton : public QPushButton
{
    Q_OBJECT

public:
    CircleButton(QString text, QWidget* parent = nullptr);
    virtual ~CircleButton() override;

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QString     m_text;
    bool        m_isHover;
    bool        m_isPressed;
};

#endif // MPUSHBUTTON_H
