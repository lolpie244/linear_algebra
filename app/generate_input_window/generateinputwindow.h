#ifndef GENERATEINPUTWINDOW_H
#define GENERATEINPUTWINDOW_H

#include <QDialog>

namespace Ui {
class GenerateInputWindow;
}

class GenerateInputWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateInputWindow(QWidget *parent = nullptr);
    ~GenerateInputWindow();
    int dimension_number;
    double min_value;
    double max_value;
	void accept();

private:
    Ui::GenerateInputWindow *ui;
};

#endif // GENERATEINPUTWINDOW_H
