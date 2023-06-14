#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

#include <QMainWindow>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QImageReader::setAllocationLimit(0);

    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Image(*.jpg *.png *.tif)"));

    QImage image(filename);
    //image.load(filename);
    image = image.scaledToWidth(ui->label->width(),Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->label->height(),Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(image));

}



void MainWindow::on_pushButton_2_clicked()
{
    QImage image = ui->label->pixmap().toImage();
        if(image.isNull())
            return;

        QImage edges = ui->label->pixmap().toImage();

        QMatrix3x3 kernel;
        kernel(0, 0) = -1; kernel(0, 1) = -1; kernel(0, 2) = -1;
        kernel(1, 0) = -1; kernel(1, 1) = 8; kernel(1, 2) = -1;
        kernel(2, 0) = -1; kernel(2, 1) = -1; kernel(2, 2) = -1;

        // Cache image dimensions
        int width = image.width() - 1;
        int height = image.height() - 1;

        // Loop over each pixel in the image
        for (int i = 1; i < width; i++) {
            for (int j = 1; j < height; j++) {

                // Cache pixel values
                QRgb topLeft = image.pixel(i-1, j-1);
                QRgb top = image.pixel(i, j-1);
                QRgb topRight = image.pixel(i+1, j-1);
                QRgb left = image.pixel(i-1, j);
                QRgb center = image.pixel(i, j);
                QRgb right = image.pixel(i+1, j);
                QRgb bottomLeft = image.pixel(i-1, j+1);
                QRgb bottom = image.pixel(i, j+1);
                QRgb bottomRight = image.pixel(i+1, j+1);

                // Compute kernel convolution
                float v = kernel(0, 0) * qGray(topLeft) +
                          kernel(0, 1) * qGray(top) +
                          kernel(0, 2) * qGray(topRight) +
                          kernel(1, 0) * qGray(left) +
                          kernel(1, 1) * qGray(center) +
                          kernel(1, 2) * qGray(right) +
                          kernel(2, 0) * qGray(bottomLeft) +
                          kernel(2, 1) * qGray(bottom) +
                          kernel(2, 2) * qGray(bottomRight);

                // Set edge pixel value
                edges.setPixel(i, j, qRgb(v, v, v));
            }
        }


        ui->label->setPixmap(QPixmap::fromImage(edges));


}

