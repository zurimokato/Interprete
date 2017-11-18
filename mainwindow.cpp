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
    if(maybeSave()){
        ui->entornoCodigo->clear();
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
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(
                    this,"Interprete - Open file","/Files",
                    "Text Files (*.txt)");
        if(!fileName.isEmpty()){
            QFile file(fileName);
            if(file.open(QFile::ReadOnly)){
                ui->entornoCodigo->setPlainText(file.readAll());
                curFile=fileName;
            }else{
                ui->Console->clear();
                ui->Console->setPlainText("Error al abrir el archivo");
            }
        }
    }

}

void MainWindow::saveFile()
{
    QFile file(curFile);
    if(file.open(QFile::WriteOnly)){
        file.write(ui->entornoCodigo->toPlainText().toUtf8());
    }else{
        ui->Console->clear();
        ui->Console->setPlainText("Error al guardar el archivo");
    }


}

void MainWindow::on_actionSaveAs_triggered()
{
    QString fileName= QFileDialog::getSaveFileName(this,"Interprete save","/Files","Text Files (*.txt)");
    curFile=fileName;
    if(!fileName.isEmpty()){
        saveFile();
    }
}

bool MainWindow::maybeSave(){
        bool modific=true;
    if(ui->entornoCodigo->document()->isModified()){
        QMessageBox::StandardButton rest=
                QMessageBox::warning(this,"Interprete Alert",
                                    tr("El documento ha sido modificado desea guardar cambios?"),
                                     QMessageBox::Yes |QMessageBox::No | QMessageBox::Cancel);

        if(rest==QMessageBox::Yes){
                on_actionSaveAs_triggered();
        }else {
            if(rest==QMessageBox::Cancel){
                    modific= false;
            }
        }
    }
    return modific;
}

void MainWindow::on_actionSave_triggered()
{
    if(curFile.isEmpty()){
        on_actionSaveAs_triggered();
    }else{
        saveFile();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }

}
