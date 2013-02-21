/*
================================
 mainwindow.h

 Created on: 20 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/


#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>


class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    
public slots:
    void setPen(QPen const& pen);
    void setBrush(QBrush const& brush);
    void setAntialiased(bool antialiased);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPen pen_;
    QBrush brush_;
    bool antialiased_;
    QPixmap pixmap_;
};

#endif // RENDERAREA_H
