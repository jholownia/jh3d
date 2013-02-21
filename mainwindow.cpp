/*
================================
 mainwindow.cpp

 Created on: 20 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderarea.h"
// #include "point.h"

#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renderArea_ = ui->renderArea;

    // int penWidth = 1;
    // Qt::PenStyle style = Qt::SolidLine;
    // Qt::PenCapStyle cap = Qt::FlatCap;
    renderArea_->setPen(QPen(Qt::blue));

    Qt::BrushStyle brush = Qt::LinearGradientPattern;
    renderArea_->setBrush(QBrush(brush));

    bool aa = true;
    renderArea_->setAntialiased(aa);

    setWindowTitle(tr("JH3D"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
