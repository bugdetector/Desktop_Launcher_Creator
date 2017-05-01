#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
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

void MainWindow::on_command_browse_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,QString::fromUtf8("Komut Seç"),"","*");
    ui->commandEdit->setText(path);
}

void MainWindow::on_icon_browse_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,QString::fromUtf8("Simge Seç"),"",tr("*.png *.jpg *.jpeg *.ico "));
    ui->iconEdit->setText(path);
}

void MainWindow::on_path_browse_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,QString::fromUtf8("Konum Seç"),NULL);
    ui->pathEdit->setText(path);
}

void MainWindow::on_save_clicked()
{
    QString filename = ui->nameEdit->text() + ".desktop";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream writer(&file);
        writer << "[Desktop Entry]" << endl;
        writer << "Encoding=UTF-8" << endl;
        writer << "Name="+ui->nameEdit->text() << endl;
        writer << "Exec="+ui->commandEdit->text() << endl;
        if(ui->commandEdit->text().compare("")){
            writer << "Comment="+ui->commentEdit->text() << endl;
        }
        if(ui->iconEdit->text().compare("")){
            writer << "Icon="+ui->iconEdit->text() << endl;
        }
        if(ui->pathEdit->text().compare("")){
            writer << "Path="+ui->pathEdit->text() << endl;
        }
        writer << "Type=Application" << endl;
        file.close();
    }
}

void MainWindow::on_iconEdit_textChanged(const QString &arg1)
{
    QPixmap image(arg1);
    image = image.scaled(ui->imageLabel->width(),ui->imageLabel->height());
    ui->imageLabel->setPixmap(image);
}

void MainWindow::on_open_button_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,QString::fromUtf8("Başlatıcı Seç"),"",tr("*.desktop "));
    if(path.compare("")){
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::information(this,"Hata","Dosya açılamadı.");
            return;
        }

        QTextStream stream(&file);
        while(!stream.atEnd()){
            QString line = stream.readLine();
            if(line.startsWith("Name=")){
                ui->nameEdit->setText(line.replace("Name=",""));
            }else if(line.startsWith("Exec=")){
                ui->commandEdit->setText(line.replace("Exec=",""));
            }else if(line.startsWith("Comment=")){
                ui->commentEdit->setText(line.replace("Comment=",""));
            }else if(line.startsWith("Icon=")){
                ui->iconEdit->setText(line.replace("Icon=",""));
            }else if(line.startsWith("Path=")){
                ui->pathEdit->setText(line.replace("Path=",""));
            }
        }
    }
}
