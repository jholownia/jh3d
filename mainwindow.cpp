/*
================================
 mainwindow.cpp

 Created on: 20 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderarea.h"
#include "renderareagl.h"
#include "model.h"
#include "jhmath.h"


// Uncomment this if building with Qt 5
// #include <QtWidgets>

/*
================
 MainWindow::MainWindow
================
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model_(NULL)
{
    ui->setupUi(this);

    // Set up UI elements
    ui->actionLoad->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionLoad->setText("Open");
    ui->actionQuit->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView));

    renderArea_ = ui->renderArea;
    gl_ = ui->renderAreaGL;

    setWindowTitle(tr("JH3D"));

    // Set up QPainter parameters
    renderArea_->setPen(QPen(Qt::blue));
    Qt::BrushStyle brush = Qt::NoBrush;
    renderArea_->setBrush(QBrush(brush));
    bool aa = true;
    renderArea_->setAntialiased(aa);

    // Default view parameters
    viewParams_.focalLength = 400;
    viewParams_.scaleX = 1;
    viewParams_.scaleY = 1;
    viewParams_.scaleZ = 1;
    viewParams_.translationX = 150;
    viewParams_.translationY = 150;
    viewParams_.translationZ = 400;
    viewParams_.rotationX = jh::PI;
    viewParams_.rotationY = 0;
    viewParams_.rotationZ = 0;
}

/*
================
 MainWindow::~MainWindow
================
*/
MainWindow::~MainWindow()
{
    delete model_;
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Model", QDir::currentPath(), "Txt Files (*.txt)");

    if (path == "")
    {
        return;
    }

    if (model_ != NULL)
    {
        delete model_;
        model_ = NULL;
    }

    using namespace jh;

    model_ = new Model;
    if (!model_->init(path.toStdString()))
    {
        QMessageBox::warning(NULL, tr("Error"), tr("Could not load model file."));
    }

    renderArea_->setModel(model_);
    renderArea_->updateView(viewParams_);

    gl_->setModel(model_);
}

void MainWindow::on_sldFocalLength_valueChanged(int value)
{
    viewParams_.focalLength = value;
    renderArea_->updateView(viewParams_);
}

void MainWindow::on_sldScaleX_valueChanged(int value)
{
    viewParams_.scaleX = value;
    if (ui->cbConstrain->isChecked())
    {
        ui->sldScaleY->setValue(value);
        ui->sldScaleZ->setValue(value);
    }
    renderArea_->updateView(viewParams_);
}

void MainWindow::on_sldScaleY_valueChanged(int value)
{
    viewParams_.scaleY = value;
    if (ui->cbConstrain->isChecked())
    {
        ui->sldScaleX->setValue(value);
        ui->sldScaleZ->setValue(value);
    }
    renderArea_->updateView(viewParams_);
}

void MainWindow::on_sldScaleZ_valueChanged(int value)
{
    viewParams_.scaleZ = value;
    if (ui->cbConstrain->isChecked())
    {
        ui->sldScaleX->setValue(value);
        ui->sldScaleY->setValue(value);
    }
    renderArea_->updateView(viewParams_);
}

void MainWindow::on_sldTranslationX_valueChanged(int value)
{
    viewParams_.translationX = value;
    renderArea_->updateView(viewParams_);    
}

void MainWindow::on_sldTranslationY_valueChanged(int value)
{
    viewParams_.translationY = value;
    renderArea_->updateView(viewParams_);    
}

void MainWindow::on_sldTranslationZ_valueChanged(int value)
{
    viewParams_.translationZ = value;
    renderArea_->updateView(viewParams_);   
}

void MainWindow::on_dialRotationX_valueChanged(int value)
{
    viewParams_.rotationX = jh::deg2Rad(value);
    renderArea_->updateView(viewParams_);    
}

void MainWindow::on_dialRotationY_valueChanged(int value)
{
    viewParams_.rotationY = jh::deg2Rad(value);
    renderArea_->updateView(viewParams_);    
}

void MainWindow::on_dialRotationZ_valueChanged(int value)
{
    viewParams_.rotationZ = jh::deg2Rad(value);
    renderArea_->updateView(viewParams_);    
}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    if (checked)
    {
        Qt::BrushStyle brush = Qt::SolidPattern;
        renderArea_->setBrush(QBrush(brush));
    }
    else
    {
        Qt::BrushStyle brush = Qt::NoBrush;
        renderArea_->setBrush(QBrush(brush));
    }

    renderArea_->updateView(viewParams_);
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    QString about("JH3D - Simple 3D rendering program\n\n");
    about += "Use File -> Open to load a model. The widget on the left side uses no 3d API, the widget on the right uses OpenGL.";
    QMessageBox::about(this, "JH3D About", about);
}

void MainWindow::on_cbDepthSort_toggled(bool checked)
{
    renderArea_->setDepthSort(checked);
}

void MainWindow::on_cbAa_toggled(bool checked)
{
    renderArea_->setAntialiased(checked);
}

void MainWindow::on_checkBox_3_toggled(bool checked)
{
    gl_->setSmooth(checked);
}

void MainWindow::on_sldLightX_valueChanged(int value)
{
    gl_->setLightPosX(static_cast<float>(value / 10.0f));
}

void MainWindow::on_sldLightY_valueChanged(int value)
{
    gl_->setLightPosY(static_cast<float>(value / 10.0f));
}

void MainWindow::on_sldLightZ_valueChanged(int value)
{
    gl_->setLightPosZ(static_cast<float>(value / 10.0f));
}

void MainWindow::on_sldGlScale_valueChanged(int value)
{
    gl_->setScale(static_cast<float>(value / 1000.0f));
}
