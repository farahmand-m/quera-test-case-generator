#ifndef QTC_GENERATOR_DRAGGABLE_BUTTON_HPP
#define QTC_GENERATOR_DRAGGABLE_BUTTON_HPP

#include <QDir>
#include <QDrag>
#include <QMimeData>
#include <QPushButton>
#include <QMouseEvent>

class DraggableButton : public QPushButton {
    Q_OBJECT
    QDrag *drag;
    QMimeData *mimeData;
public slots:
    void mousePressEvent(QMouseEvent *event);
public:
    explicit DraggableButton(QString label, QWidget *parent = nullptr);
};

#endif
