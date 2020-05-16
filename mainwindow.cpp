#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_ui();

}

MainWindow::~MainWindow()
{
    delete ui;
}
\
void MainWindow:: update_ui () {


    this->ui->spinScale->setValue(this->ui->renderArea->scale());
    this->ui->spinInterval->setValue(this->ui->renderArea->intervalLength());
    this->ui->spinCount->setValue(this->ui->renderArea->stepCount());


}


void MainWindow::on_btnAsteroid_clicked()
{

    this->ui->renderArea->setShape(RenderArea::Asteroid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{

    this->ui->renderArea->setShape(RenderArea::Cycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{

    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHypo_clicked()
{

    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnline_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    this->ui->renderArea->repaint();
    update_ui();

}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->setScale(scale);
}

void MainWindow::on_spinInterval_valueChanged(double length)
{
    this->ui->renderArea->setInterval(length);
}

void MainWindow::on_spinCount_valueChanged(int count)
{
    this->ui->renderArea->setStepCount(count);
}

void MainWindow::on_btnBackGround_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->backgroundColor(),this,"Select BackGround Color");
    ui->renderArea->setBackgroundColor(color);
}

void MainWindow::on_btnLineColor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->shapeColor(),this,"Select Shape Color");
    ui->renderArea->setShapeColor(color);

}

void MainWindow::on_btnCircle_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Circle);
    this->ui->renderArea->repaint();
    update_ui();

}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_btnEllipse_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Ellipse);
    this->ui->renderArea->repaint();
    update_ui();

}

void MainWindow::on_btnfancy_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Fancy);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnstar_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Star);
    this->ui->renderArea->repaint();
    update_ui();

}
