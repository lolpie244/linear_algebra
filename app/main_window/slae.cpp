#include "slae.h"
#include "../generate_input_window/generateinputwindow.h"
#include "./ui_slae.h"
#include "linear_system_methods/linear_system_methods.h"
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
	ui->SelectMethod->clear();
	for (auto key :
	        linear_systems_solvers_list::LinearSystemMethodsInfo().methods_list())
		ui->SelectMethod->addItem(QString::fromStdString(key.first));

	ui->SelectMethod->setCurrentIndex(0);
}

Slae::~Slae()
{
	delete ui;
}
void ErrorMessage(const std::exception &ex)
{
	QMessageBox message_box;
	message_box.critical(0, "Error", QString::fromStdString(ex.what()));
}

void Slae::update_coeficient_matrix()
{
	ui->matrixTable->setRowCount(solver->coeficient_matrix.size().first);
	ui->matrixTable->setColumnCount(solver->coeficient_matrix.size().second);
	for (int i = 0; i < solver->coeficient_matrix.size().first; i++)
		for (int j = 0; j < solver->coeficient_matrix.size().second; j++)
			ui->matrixTable->setItem(i, j,
			                         new QTableWidgetItem(QString::number(
			                                     solver->coeficient_matrix[i][j])));
}

void Slae::update_constants_vector()
{
	ui->constantsVector->setRowCount(solver->constants_vector.size());
	for (int i = 0; i < solver->constants_vector.size(); i++)
		ui->constantsVector->setItem(
		    i, 0,
		    new QTableWidgetItem(QString::number(solver->constants_vector[i])));
}

void Slae::update_solution_vector()
{
	auto solution_vector = solver->get_solution_vector();
	ui->solutionVector->setColumnCount(solution_vector.size());
	for (int i = 0; i < solution_vector.size(); i++)
		ui->solutionVector->setItem(
		    0, i, new QTableWidgetItem(QString::number(solution_vector[i])));
}

void Slae::update_input_screen()
{
	ui->StartButton->setEnabled(true);
	solver->clear();
	update_coeficient_matrix();
	update_constants_vector();
	update_solution_vector();
}

void Slae::on_LoadFromFileButton_clicked()
{
	QString filter = tr("Text (*.txt)");
	QString filename = QFileDialog::getOpenFileName(this, "Open File", "/home",
	                   tr("TXT (*.txt)"), &filter);

	if (filename != "") {
		linear_systems::GaussianSolver new_solver;

		try {
			solver = file_processor->read_from_file(filename.toStdString());
		} catch (const std::exception &ex) {
			ErrorMessage(ex);
			return;
		}

		update_input_screen();
	}
}

void Slae::on_GenerateButton_clicked()
{
	GenerateInputWindow input_dialog;
	if (input_dialog.exec() == QDialog::Accepted) {
		pair<size_t, size_t> size = {input_dialog.dimension_number,
		                             input_dialog.dimension_number + 1
		                            };
		solver->coeficient_matrix = matrix::Matrix::get_random(
		                                size, input_dialog.min_value, input_dialog.max_value);
		solver->constants_vector =
		    solver->coeficient_matrix.erase_column(size.second - 1);
		update_input_screen();
	}
}

void Slae::on_SaveToFileButton_clicked()
{
	QString filter = tr("Text (*.txt)");
	QString filename = QFileDialog::getSaveFileName(this, "Open File", "/home",
	                   tr("TXT (*.txt)"), &filter);

	if (filename != "") {
		file_processor->write_to_file(filename.toStdString(), solver);
	}
}

void Slae::on_matrixTable_cellChanged(int row, int column)
{
	solver->coeficient_matrix[row][column] =
	    ui->matrixTable->item(row, column)->text().toDouble();
	solver->clear();
}

void Slae::on_constantsVector_cellChanged(int row, int column)
{
	solver->constants_vector[row] =
	    ui->constantsVector->item(row, column)->text().toDouble();
	solver->clear();
}

map<QString, QString> Slae::get_information()
{
	map<QString, QString> information;

	information["Matrix norm"] =
	    QString::number(solver->coeficient_matrix.get_norm());
	information["System dimension"] =
	    QString::number(solver->coeficient_matrix.size().first);

	if (solver->get_solution_vector().size())
		information["Measurement error"] =
		    QString::number(solver->get_measurement_error());

	return information;
}
void Slae::on_matrixInfo_clicked()
{
	auto information = this->get_information();
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
	solver->coeficient_matrix.resize({new_size, new_size});
	solver->constants_vector.resize(new_size);

	update_input_screen();
}

void Slae::on_SelectMethod_currentIndexChanged(int index)
{
	std::string method = ui->SelectMethod->currentText().toStdString();
	auto linear_method =
	    linear_systems_solvers_list::LinearSystemMethodsInfo().get(method);
	solver = linear_method.solver;
	file_processor = linear_method.file_processor;
}

void Slae::on_StartButton_clicked()
{

	try {
		solver->solve();
	} catch (const std::exception &ex) {
		ErrorMessage(ex);
		return;
	}
	update_solution_vector();
}

void Slae::on_inverseButton_clicked()
{

	try {
		solver->inverse();
	} catch (const std::exception &ex) {
		ErrorMessage(ex);
		return;
	}
	update_input_screen();
}
