#ifndef HORIZONTALBUTTON_H
#define HORIZONTALBUTTON_H

#include <QPushButton>
#include <QLineEdit>

#define PAINT

class HorizontalButton : public QPushButton
{
    Q_OBJECT

public:
    HorizontalButton(QString text, bool rotated = false, QWidget *parent = nullptr);
    virtual ~HorizontalButton() override;

protected:

    void paintEvent(QPaintEvent *event) override;


    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

//private:
//    QSize getTextSize(const QString& text);

private:
    QString     m_text;
    bool        m_isRotated;
    bool        m_isHover;
    bool        m_isPressed;
};

#endif // MPUSHBUTTON_H
