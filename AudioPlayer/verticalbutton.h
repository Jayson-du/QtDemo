#ifndef VERTICALBUTTON_H
#define VERTICALBUTTON_H

#include <QPushButton>
#include <QString>

class VerticalButton : public QPushButton
{
    Q_OBJECT

public:
    VerticalButton(QString text, bool rotated = false, QWidget* parent = nullptr);
    virtual ~VerticalButton() override;

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;


private:
    QString     m_text;
    bool        m_isRotated;
    bool        m_isHover;
    bool        m_isPressed;
};

#endif

