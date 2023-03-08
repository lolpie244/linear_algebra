#include "generateinputwindow.h"
#include "ui_generateinputwindow.h"

GenerateInputWindow::GenerateInputWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateInputWindow)
{
    ui->setupUi(this);
}

void GenerateInputWindow::accept()
{
    dimension_number = ui->dimensionNumber->value();
    min_value = ui->minValue->value();
    max_value = ui->maxValue->value();
	QDialog::accept();
}

GenerateInputWindow::~GenerateInputWindow()
{
    delete ui;
}
