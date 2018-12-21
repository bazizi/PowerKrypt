#include "keygen.h"
#include <QtDebug>
#include <QFileDialog>
#include <fstream>
#include <random>

KeyGenerator::KeyGenerator(QWidget * parent):
    QDialog(parent)
{
    setupUi(this);
    connect(this, SIGNAL(on_progress_changed(int)), progressBar, SLOT(setValue(int)));
}

KeyGenerator::~KeyGenerator()
{

}

void KeyGenerator::Display()
{

}


void KeyGenerator::GenerateRandomKey(const QString& keyPath, const int& keySize)
{
    if (keyPath.isEmpty()) return;
    std::ofstream os(keyPath.toStdString(), std::ios::binary);
//    os << m_signature.toStdString();
    // generate a 5MB key
    int cbKey = keySize;
    while (cbKey > 0)
    {
        std::random_device rd;
        unsigned int val = rd();
        os.write(reinterpret_cast<const char*>(&val), (sizeof(val) < static_cast<size_t>(cbKey))? sizeof(val) : cbKey );
        emit on_progress_changed( static_cast<int> ((keySize - cbKey + 1) * 100 / keySize) );
        cbKey -= sizeof(val);
    }
    os.close();
}

void KeyGenerator::on_keyGenButton_clicked()
{
    QString fileToSave = QFileDialog::getSaveFileName(this, QString("Select location to save encryption key ..."), QDir::homePath(), tr("PowerKrypt Encryption Key (*.pkk)"));
    if (!fileToSave.endsWith(".pkk"))
    {
        fileToSave += ".pkk";
    }

    filePath->setText( fileToSave );
    const int cmbKeySize = static_cast<int>(std::atoi(keySize->text().toStdString().c_str()) * pow(2, 20));
    GenerateRandomKey(filePath->text(), cmbKeySize);
}

void KeyGenerator::on_sliderKeySize_valueChanged(int value)
{
    keySize->setText(QString::number(value));
}
