#include "widget.h"
#include "ui_widget.h"
#include <regex>
#include <string>
#include <QValidator>
#include <QRegExp>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(350,150);
    setWindowTitle("UPC/EAN Barcode Validator");
    ui->outcomeLabel->setText("");

    QValidator *val= new QRegExpValidator(QRegExp("[0-9]{12,13}"),this);
    ui->barcodeEdit->setValidator(val);

    connect(ui->barcodeEdit,&QLineEdit::textChanged,this,&Widget::checker);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::checker(void)
{
    std::string barCodeString=ui->barcodeEdit->text().toStdString();
    int digitExp=0;

    if (barCodeString.length() <12)
        ui->outcomeLabel->setText("Number of entered digits: "+QString::number(barCodeString.length()));

    if (barCodeString.length() == 12)
    {
        for (size_t idx=0; idx<barCodeString.length()-1; idx++)
        {
            if (idx%2==0)
                digitExp += 3*std::stoi(barCodeString.substr(idx,1));
            else
                digitExp += std::stoi(barCodeString.substr(idx,1));
        }
        digitExp %= 10;

        if (digitExp!=0)
            digitExp = 10 - digitExp;

        if (std::to_string(digitExp) == barCodeString.substr(barCodeString.length()-1))
            ui->outcomeLabel->setText("Valid 12-digit UPC barcode!");
        else
            ui->outcomeLabel->setText("Invalid 12-digit UPC barcode!");
    }

    if (barCodeString.length() == 13)
    {
        for (size_t idx=0; idx<barCodeString.length()-1; idx++)
        {
            if (idx%2==0)
                digitExp += std::stoi(barCodeString.substr(idx,1));
            else
                digitExp += 3*std::stoi(barCodeString.substr(idx,1));
        }
        digitExp %= 10;

        if (digitExp!=0)
            digitExp = 10 - digitExp;

        if (std::to_string(digitExp) == barCodeString.substr(barCodeString.length()-1))
            ui->outcomeLabel->setText("Valid 13-digit EAN barcode!");
        else
            ui->outcomeLabel->setText("Invalid 13-digit EAN barcode!");
    }
}
