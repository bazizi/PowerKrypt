#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

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
    void on_pushButton_3_clicked();
    void on_actionAbout_triggered();

private:
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
    void GenerateRandomKey(const QString &keyPath);
};

#endif // MAINWINDOW_H
