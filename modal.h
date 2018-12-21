#ifndef MODAL_H
#define MODAL_H

#include <QDialog>

namespace Ui {
class Modal;
}

class Modal : public QDialog
{
    Q_OBJECT

public:
    explicit Modal(QWidget *parent = nullptr);
    ~Modal();

private:
    Ui::Modal *ui;
};

#endif // MODAL_H
