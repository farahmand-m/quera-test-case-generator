#include "DraggableButton.hpp"

void DraggableButton::mousePressEvent(QMouseEvent *event) {
    system(("rm \"" + QDir::currentPath() + "/problem/problem.zip\"").toLocal8Bit().data());
    system(("cd \"" + QDir::currentPath() + "/problem\" && zip -r problem.zip in out").toLocal8Bit().data());

    mimeData = new QMimeData;
    mimeData->setUrls(QList<QUrl> () << QUrl::fromLocalFile(QDir::currentPath() + "/problem/problem.zip"));
    drag = new QDrag(this);
    drag->setMimeData(mimeData);
    Qt::DropAction dropAction = drag->exec();
}

DraggableButton::DraggableButton(QString label, QWidget *parent) {
    setText(label);
    setParent(parent);
}