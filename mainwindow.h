/*
================================
 mainwindow.h

 Created on: 20 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewparams.h"

class RenderArea;
class RenderAreaGL;

namespace jh
{
    class Model;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionLoad_triggered();

    void on_sldFocalLength_valueChanged(int value);

    void on_sldScaleX_valueChanged(int value);

    void on_sldScaleY_valueChanged(int value);

    void on_sldScaleZ_valueChanged(int value);

    void on_sldTranslationX_valueChanged(int value);

    void on_sldTranslationY_valueChanged(int value);

    void on_sldTranslationZ_valueChanged(int value);

    void on_dialRotationX_valueChanged(int value);

    void on_dialRotationY_valueChanged(int value);

    void on_dialRotationZ_valueChanged(int value);

    void on_checkBox_2_toggled(bool checked);

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_cbDepthSort_toggled(bool checked);

    void on_cbAa_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_sldLightX_valueChanged(int value);

    void on_sldLightY_valueChanged(int value);

    void on_sldLightZ_valueChanged(int value);

    void on_sldGlScale_valueChanged(int value);

private:
    Ui::MainWindow* ui;
    RenderArea* renderArea_;
    RenderAreaGL* gl_;
    jh::Model* model_;
    ViewParams viewParams_;
};

#endif // MAINWINDOW_H
