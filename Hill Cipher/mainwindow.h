#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    int mod(int a, int b);
    int modInv(int a, int b);
    void NormalizeString(QString* ptext);
    QString BuildInvKey(int key[2][2], int akey[2][2]);
    QString Encrypt(int matrix[2][2], QString ptext);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
