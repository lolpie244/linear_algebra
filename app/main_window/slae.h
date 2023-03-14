#ifndef SLAE_H
#define SLAE_H

#include "file_processors/file_processors.h"
#include "linear_systems_solvers/base_linear_system_solver.h"
#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Slae;
}
QT_END_NAMESPACE

class Slae : public QMainWindow
{
	Q_OBJECT

public:
	Slae(QWidget *parent = nullptr);

	~Slae();

private slots:

	void on_LoadFromFileButton_clicked();
	void on_GenerateButton_clicked();
	void on_SaveToFileButton_clicked();
	void on_matrixTable_cellChanged(int row, int column);
	void on_constantsVector_cellChanged(int row, int column);
	void on_matrixInfo_clicked();
	void on_resizeButton_clicked();

    void on_SelectMethod_currentIndexChanged(int index);

    void on_StartButton_clicked();

    void on_inverseButton_clicked();

private:
	Ui::Slae *ui;
	std::shared_ptr<file_processor::BaseFileProcessor<std::shared_ptr<linear_systems::BaseLinearSystemSolver>>> file_processor;
	std::shared_ptr<linear_systems::BaseLinearSystemSolver> solver;
	
	void update_input_screen();
	void update_coeficient_matrix();
	void update_constants_vector();
	void update_solution_vector();
};
#endif // SLAE_H
