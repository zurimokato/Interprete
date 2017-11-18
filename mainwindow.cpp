#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{
    QString fileName= QFileDialog::getSaveFileName(this,"Interprete save","/Files","Text Files (*.txt)");
    curFile=fileName;
    if(!fileName.isEmpty()){
        saveFile();
    }
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_actionRun_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{


}

void MainWindow::saveFile()
{
    QFile file(curFile);
    if(file.open(QFile::WriteOnly)){
        file.write(ui->entornoCodigo->toPlainText().toUtf8());
    }else{
        QMessageBox::warning(
                    this,"TextEditor",tr("Error").arg(curFile).arg(file.errorString()));
    }


}
