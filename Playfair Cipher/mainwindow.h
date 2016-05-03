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

    void FindInKernel(QChar kernel[5][5], QChar ch, int* x,int* y);
    void AddToKernel(QChar kernel[5][5]  , QChar key, int* currentY, int* currentX);
    void CheckAddToKernel(int* currentX, QChar kernel[5][5], int* currentY, QChar token);
    void BuildKernel(QString key, QChar kernel[5][5]);
    void NormalizeString(QString* ptext);
    void FixDuplicateChar(QString* ptext);
    void RemoveXForDuplicates(QString* ptext);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
