#include "slae.h"
#include "./ui_slae.h"
#include "app/generate_input_window/generateinputwindow.h"
#include "only_number_delegate.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <map>
#include <qinputdialog.h>
#include <qtableview.h>
#include <utility>

using std::map;
using std::pair;

Slae::Slae(QWidget *parent) : QMainWindow(parent), ui(new Ui::Slae)
{
	ui->setupUi(this);
	ui->matrixTable->setItemDelegate(new Delegate);
	ui->constantsVector->setItemDelegate(new Delegate);
}

Slae::~Slae()
{
	delete ui;
}

void Slae::update_coeficient_matrix()
{
	ui->matrixTable->setRowCount(coeficient_matrix.size().first);
	ui->matrixTable->setColumnCount(coeficient_matrix.size().second);
	for (int i = 0; i < coeficient_matrix.size().first; i++)
		for (int j = 0; j < coeficient_matrix.size().second; j++)
			ui->matrixTable->setItem(
			    i, j, new QTableWidgetItem(QString::number(coeficient_matrix[i][j])));
}

void Slae::update_constants_vector()
{
	ui->constantsVector->setRowCount(constants_vector.size());
	for (int i = 0; i < constants_vector.size(); i++)
		ui->constantsVector->setItem(
		    i, 0, new QTableWidgetItem(QString::number(constants_vector[i])));
}

void Slae::update_screen()
{
	update_coeficient_matrix();
	update_constants_vector();
}

void Slae::on_LoadFromFileButton_clicked()
{
	QString filter = tr("Text (*.txt)");
	QString filename = QFileDialog::getOpenFileName(this, "Open File", "/home",
	                   tr("TXT (*.txt)"), &filter);

	if (filename != "") {
		matrix::Matrix new_matrix;

		try {
			new_matrix = file_processor.read_from_file(filename.toStdString());
			if (new_matrix.size().first + 1 != new_matrix.size().second)
				throw "incorrect coeficient matrix size";
		} catch (...) {
			QMessageBox message_box;
			message_box.critical(0, "Error", "Incorrect coeficient matrix");
			return;
		}
		coeficient_matrix = std::move(new_matrix);
		constants_vector = std::move(coeficient_matrix.get_column(coeficient_matrix.size().second - 1));

		coeficient_matrix.resize({coeficient_matrix.size().first, coeficient_matrix.size().first});

		update_screen();
	}
}

void Slae::on_GenerateButton_clicked()
{
	GenerateInputWindow input_dialog;
	if (input_dialog.exec() == QDialog::Accepted) {
		pair<size_t, size_t> size = {input_dialog.dimension_number,
		                             input_dialog.dimension_number + 1
		                            };
		coeficient_matrix = matrix::Matrix::get_random(size, input_dialog.min_value,
		                    input_dialog.max_value);
		constants_vector = coeficient_matrix.get_column(size.second - 1);
		coeficient_matrix.resize({size.first, size.first});
		update_screen();
	}
}

void Slae::on_SaveToFileButton_clicked()
{
	QString filter = tr("Text (*.txt)");
	QString filename = QFileDialog::getSaveFileName(this, "Open File", "/home",
	                   tr("TXT (*.txt)"), &filter);

	if (filename != "") {
		auto to_write_matrix = coeficient_matrix;
		to_write_matrix.insert_column(coeficient_matrix.size().second,
		                              constants_vector);
		file_processor.write_to_file(filename.toStdString(), to_write_matrix);
	}
}

void Slae::on_matrixTable_cellChanged(int row, int column)
{
	coeficient_matrix[row][column] =
	    ui->matrixTable->item(row, column)->text().toDouble();
}

void Slae::on_constantsVector_cellChanged(int row, int column)
{
	constants_vector[row] =
	    ui->constantsVector->item(row, column)->text().toDouble();
}

void Slae::on_matrixInfo_clicked()
{
	map<QString, QString> information;

	information["Matrix norm"] = QString::number(coeficient_matrix.get_norm());
	information["System dimension"] =
	    QString::number(coeficient_matrix.size().first);

	QTableWidget *table = new QTableWidget();
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->hide();
	table->verticalHeader()->hide();
	table->setRowCount(information.size());
	table->setColumnCount(2);
	table->setColumnWidth(0, 160);
	table->setColumnWidth(1, 90);
	int i = 0;
	for (auto [key, value] : information) {
		table->setItem(i, 0, new QTableWidgetItem(key));
		table->setItem(i, 1, new QTableWidgetItem(value));
		i++;
	}

	QMainWindow *window = new QMainWindow();
	window->setWindowTitle("Coeficient matrix detail");
	window->setCentralWidget(table);
	window->show();
}

void Slae::on_resizeButton_clicked()
{
	QInputDialog dialog;
	auto new_size = QInputDialog::getInt(
	                    0, "Resize", "Input new number of system dimensions", 0, 2);
	if (new_size == 0)
		return;
	coeficient_matrix.resize({new_size, new_size});
	constants_vector.resize(new_size);

	update_screen();
}
