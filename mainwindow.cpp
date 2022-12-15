#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <iostream>
#include <QString>
#include <QFileDialog>
#include <QLayout>
#include <QPushButton>
#include <QItemSelectionModel>
#include <QImageReader>
#include <QTableWidget>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout(this->centralWidget());

    compression["bmp"] = "No compression";
    compression["gif"] = "LZW compression";
    compression["png"] = "Deflate compression";
    compression["jpg"] = "JPEG compression";
    compression["tiff"] = "ZIP/LZW/JPEG compression";
    compression["pcx"] = "RLE compression";


    QTableWidget *mainTable = new QTableWidget(1, 1, this);
    mainTable->setColumnCount(5);
    mainTable -> setHorizontalHeaderLabels({"Name", "Size", "Resolution", "глубина цвета", "сжатие"});
    mainTable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(mainTable, 0, 0);

    QString pathToFolder = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    QDir currentFolder(pathToFolder);

    QStringList images = currentFolder.entryList(QStringList() << "*.bmp" << "*.BMP" << "*.jpg" << "*.JPG" << "*.gif" << "*.GIF"<< "*.png" << "*.PNG" << "*.tiff" << "*.TIFF" << "*.pcx" << "*.PCX",QDir::Files);


    QStringList filter;
    filter << QLatin1String("*.bmp");
    filter << QLatin1String("*.BMP");

    filter << QLatin1String("*.jpg");
    filter << QLatin1String("*.JPG");

    filter << QLatin1String("*.gif");
    filter << QLatin1String("*.GIF");


    filter << QLatin1String("*.png");
    filter << QLatin1String("*.PNG");


    filter << QLatin1String("*.tiff");
    filter << QLatin1String("*.TIFF");

    filter << QLatin1String("*.pcx");
    filter << QLatin1String("*.PCX");
    currentFolder.setNameFilters(filter);
    QFileInfoList filelistinfo = currentFolder.entryInfoList();


    for(int i = 0; i < images.size(); i++){
        mainTable -> insertRow(mainTable -> rowCount() - 1);

        QFileInfo &fileinfo = filelistinfo[i];
        QString currentImageName = fileinfo.absoluteFilePath();
        QImage currentImage = QImage(currentImageName);

        QString filename = images [i];
        mainTable->setItem(i, 0, new QTableWidgetItem(filename));


        QString sizeStr = QString::number(currentImage.size().width()) + "x" + QString::number(currentImage.size().height());
        mainTable->setItem(i, 1, new QTableWidgetItem(sizeStr));

        QString resolutionInfo = QString::number(round((std::min(currentImage.dotsPerMeterX(), currentImage.dotsPerMeterY()) / 39.37)));
        mainTable->setItem(i, 2, new QTableWidgetItem(resolutionInfo));


        QString depthStr = QString::number(currentImage.depth());
        mainTable->setItem(i, 3, new QTableWidgetItem(depthStr));

        mainTable -> setItem(i, 4, new QTableWidgetItem(QString(compression[fileinfo.suffix().toLower()])));

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

