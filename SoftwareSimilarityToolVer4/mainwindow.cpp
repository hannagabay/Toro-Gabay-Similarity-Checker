#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QLabel>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iomanip>
#include<qlistwidget.h>
#include <qmath.h>
#include <qstandardpaths.h>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString autoexec = QString("%1/autoexec.cfg").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    foreach(QFileInfo var, dir.entryInfoList()){
        ui->comboBox->addItem(var.absoluteFilePath());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


double getSimilarity(string fileName1, string fileName2) {
    double similar = 0, total = 0;
    string line1, line2, temp;
    int length1, length2;

    ifstream file1;
    file1.open (fileName1.c_str(), ios::binary );
    file1.seekg (0, ios::end);
    length1 = file1.tellg();
    file1.close();


    ifstream file2;
    file2.open (fileName2.c_str(), ios::binary );
    file2.seekg (0, ios::end);
    length2 = file2.tellg();
    file2.close();

    if (length2 > length1) {
        temp = fileName1;
        fileName1 = fileName2;
        fileName2 = temp;
    }

    file1.open(fileName1.c_str());

    while ( getline(file1, line1) ) {
        if (line1.find_first_not_of(' ') == std::string::npos) continue;
        file2.open(fileName2.c_str());
        while ( getline(file2, line2) ) {
            if (strcmp(line1.c_str(), line2.c_str()) == 0) {
                similar += 1.0;
                break;
            }
        }
        file2.close();

        total += 1.0;
    }
    file1.close();
    return similar/total*100;
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();
    QDir dir(ui->comboBox->currentText());
    foreach(QFileInfo var, dir.entryInfoList()){
        if(var.isFile()){
            ui->listWidget->addItem(var.absoluteFilePath());
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    QDir dir(ui->comboBox->currentText());

    int filecount = ui->listWidget->count();
    cout<<filecount<<endl;
    string fileNames[35];
    int z=0;
    foreach(QFileInfo var, dir.entryInfoList()){
        if(var.isFile()){
            fileNames[z]= var.absoluteFilePath().toLocal8Bit().constData();
            cout<<fileNames[z]<<endl;
            z++;
        }
    }
    int x,y;
    double SimilarityScores[filecount][filecount];
    for (y=0;y<filecount;y++) {
        for (x=0;x<filecount;x++) {
            SimilarityScores[x][y] =getSimilarity(fileNames[y],fileNames[x]);

        }
    }


    for (y = 0; y < filecount; y++) {
        for (x = 0; x < filecount; x++) {
            double nearest = roundf(SimilarityScores[x][y] * 100) / 100;
            QString valueAsString = QString::number(nearest);
            ui->tableWidget->setRowCount(filecount);
            ui->tableWidget->setColumnCount(filecount);
            ui->tableWidget->setItem(x,y,new QTableWidgetItem(valueAsString));
            if(nearest==100){
                ui->tableWidget->item(x,y)->setBackground(Qt::red);
            }
            else if(nearest<20){
                ui->tableWidget->item(x,y)->setBackground(Qt::blue);
            }
            else if(nearest<40){
                ui->tableWidget->item(x,y)->setBackground(Qt::green);
            }
            else if(nearest<60){
                ui->tableWidget->item(x,y)->setBackground(Qt::yellow);
            }
            else if(nearest<80){
                ui->tableWidget->item(x,y)->setBackground(Qt::magenta);
            }


        }
    }

}
