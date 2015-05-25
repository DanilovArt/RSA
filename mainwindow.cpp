#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Enigma");
    ui->pushButton_3->show();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_5->hide();
    ui->textEdit->hide();
    ui->textEdit_2->hide();
    ui->textEdit_3->hide();
    ui->textEdit_4->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButton_4->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{

    ui->pushButton_3->hide();
    worker=new RSA;
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->textEdit->show();
    ui->textEdit_2->show();
    ui->textEdit_3->show();
    ui->textEdit_4->show();
    ui->label->show();
    ui->label_2->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
}
void MainWindow::on_pushButton_2_clicked()
{
    QString  ee,nn;
    ee=ui->textEdit_3->toPlainText();
    nn=ui->textEdit_4->toPlainText();

    QString input=ui->textEdit->toPlainText();
    std::string text= input.toStdString();
    BigInt message(text);
    BigInt result;

    if(ee.isEmpty()||nn.isEmpty()){

    worker->encrypt(result,message);
    }
    else
    {
        std::string estr,nstr;
        estr=ee.toStdString();
        nstr=nn.toStdString();
        BigInt e(estr);
        BigInt n(nstr);

        worker->encrypt(result,message,e,n);

    }
    QString out;
    out=biginttostr(result);
    ui->textEdit_2->setText(out);

}


void MainWindow::on_pushButton_4_clicked()
{
  ui->textEdit->setText(ui->textEdit_2->toPlainText());
  ui->textEdit_2->clear();
}

void MainWindow::on_pushButton_clicked()
{
    QString input=ui->textEdit->toPlainText();
    std::string text=input.toStdString();
    BigInt message(text);
    BigInt result;
    worker->decrypt(message,result);
    ui->textEdit_2->setText(biginttostr(result));

}



void MainWindow::on_pushButton_5_clicked()
{
   BigInt ee,nn;
   worker->PublicKey(ee,nn);
   ui->textEdit_3->setText(biginttostr(ee));
   ui->textEdit_4->setText(biginttostr(nn));
}


