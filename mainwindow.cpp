#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <random>
#include <math.h>
#include <fstream>
#include <QtDebug>
#include "ui_about.h"
#include <QtDebug>

using BYTE = unsigned char;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_KeyGenerator(parent)
{
    m_signature = "PowerKrypt v1.1\n";
    m_config.insert(RECENTKEYS, {});
    m_config.insert(RECENTFILES, {});

    ui->setupUi(this);

    LoadSettings();

    QString keyPath = QDir::homePath() + QDir::separator() + "PowerKrypt.pkk";
    if (!ui->recentKeys->count() || !CheckFileExists(keyPath))
    {
        m_KeyGenerator.GenerateRandomKey(keyPath);
        ui->recentKeys->insertItem(0, keyPath);
        m_config[RECENTKEYS].insert(ui->recentKeys->itemText(ui->recentKeys->count() - 1));
    }
}

MainWindow::~MainWindow()
{
    SaveSettings();
    delete ui;
}

void MainWindow::on_browseFileButton_clicked()
{
    QString itemToInsert;
    if(ui->isDirectory->isChecked())
    {
        itemToInsert = QFileDialog::getExistingDirectory(this, QString("dir"), QDir::homePath()) + QDir::separator();
    }
    else
    {
        itemToInsert = QFileDialog::getOpenFileName(this, QString("dir"), QDir::homePath());
    }

    // if item does not exit in dropdown insert it
    if (!m_config[RECENTFILES].contains(itemToInsert) && itemToInsert != "")
    {
        ui->recentFiles->insertItem(ui->recentFiles->count() - 1, itemToInsert);
        m_config[RECENTFILES].insert(itemToInsert);
    }
}

void MainWindow::LoadSettings()
{
    QFile file(QDir::homePath() + QDir::separator() + ".PowerKrypt");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> m_config;
    const std::array<QString, 2> keys =
    {
        RECENTFILES,
        RECENTKEYS
    };
    for (const auto& key : keys)
    {
        for (const auto& filePath: m_config[key])
        {
            if (filePath == "") continue;
            if ( key == RECENTFILES)
            {
                this->ui->recentFiles->insertItem(0, filePath);
            }
            else if (key == RECENTKEYS)
            {
                this->ui->recentKeys->insertItem(0, filePath);
            }
        }
    }
    bool checked;
    in >> checked;
    this->ui->isDirectory->setChecked(checked);
    file.close();
}

void MainWindow::SaveSettings()
{
    QFile file(QDir::homePath() + QDir::separator() + ".PowerKrypt");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << m_config << this->ui->isDirectory->isChecked();
}

bool MainWindow::CheckFileExists(const QString& path)
{
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile();
}

void MainWindow::on_actionAbout_triggered()
{
    QDialog about (this, nullptr);
    Ui_About aboutUi;
    aboutUi.setupUi(&about);
    about.exec();
}


void MainWindow::on_keyGenButton_clicked()
{
    m_KeyGenerator.exec();
}
