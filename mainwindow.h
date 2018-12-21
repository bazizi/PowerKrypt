#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "keygen.h"

#define RECENTFILES     "recentFiles"
#define RECENTKEYS      "recentKeys"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();
    void on_keyGenButton_clicked();
    void on_browseFileButton_clicked();

private:
    KeyGenerator m_KeyGenerator;
    Ui::MainWindow *ui;
    void LoadSettings();
    void SaveSettings();
    QMap<QString, QSet<QString>> m_config;
    QString m_signature; // signature added to beginnint of pkk file
    /**
     config format:
        {
            recentFiles:
            [
                {
                    path-to-file
                }
            ],
            indexOfSelectedRecentFile,
            recentKeys:
            [
                {
                    path-to-key
                }
            ],
            indexOfSelectedRecentKey
        }

     **/

    bool CheckFileExists(const QString &path);
};

#endif // MAINWINDOW_H
