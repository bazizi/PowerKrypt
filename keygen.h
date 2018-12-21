#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <QWidget>
#include "ui_keygen.h"
#include <QDialog>
#include <math.h>

class KeyGenerator : public QDialog, public Ui::KeyGen
{
   Q_OBJECT
public:
    KeyGenerator(QWidget * parent = nullptr);
    ~KeyGenerator();
    void Display();
    void GenerateRandomKey(const QString &keyPath, const int& keySize = static_cast<int>(5 * pow(2, 20)));

signals:
    void on_progress_changed(int value);

private slots:
    void on_keyGenButton_clicked();
    void on_sliderKeySize_valueChanged(int value);
};

#endif // KEYGENERATOR_H
