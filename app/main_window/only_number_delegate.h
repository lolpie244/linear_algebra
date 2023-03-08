#include <QItemDelegate>
#include <QLineEdit>
#include <qvalidator.h>

class Delegate : public QItemDelegate
{
public:
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	                      const QModelIndex &index) const
	{
		QLineEdit *lineEdit = new QLineEdit(parent);
		// Set validator
		auto *validator = new QDoubleValidator(lineEdit);
		lineEdit->setValidator(validator);
		return lineEdit;
	}
};
