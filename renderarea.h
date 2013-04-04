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

#include "model.h"
#include "viewparams.h"


/*
================================

 RenderArea

 A 2D render area which uses QPixmap, QPainter
 and transformation matrices for drawing 3D shapes.

================================
*/
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
    void setModel(jh::Model* model);
    void updateView(ViewParams viewParams);
    void setDepthSort(bool sort);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPen pen_;
    QBrush brush_;
    bool antialiased_;
    QPixmap pixmap_;    
    ViewParams viewParams_;
    jh::Model* model_;
    bool depthSort_;
};

#endif // RENDERAREA_H
