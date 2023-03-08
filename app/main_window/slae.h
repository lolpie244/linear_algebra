#ifndef SLAE_H
#define SLAE_H

#include <QMainWindow>
#include<memory>
#include "src/structures/matrix/matrix.h"
#include "src/structures/vector/vector.h"
#include "src/file_processors/file_processors.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Slae; }
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

private:
    Ui::Slae *ui;
	file_processor::MatrixFileProcessor file_processor;
    matrix::Matrix coeficient_matrix;
    vector::Vector constants_vector;
    vector::Vector result_vector;

	void update_screen();
	void update_coeficient_matrix();
	void update_constants_vector();

};
#endif // SLAE_H
