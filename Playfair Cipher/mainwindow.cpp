#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FindInKernel(QChar kernel[5][5], QChar ch, int* x,int* y)
{
    *x = *y = -1;
    for(int j=0; j<5; j++)
        for(int i = 0; i<5; i++)
            if(kernel[j][i] == ch)
            {
                *x = i;
                *y = j;
                return;
            }
}

void MainWindow::AddToKernel(QChar kernel[5][5], QChar ch, int* currentY, int* currentX)
{
    kernel[*currentY][*currentX] = ch;
    (*currentX)++;

    if(*currentX == 5)
    {
        (*currentY)++;
        *currentX = 0;
    }
}

void MainWindow::CheckAddToKernel(int* currentX, QChar kernel[5][5], int* currentY, QChar token)
{
    int x,y;
    FindInKernel(kernel,token,&x,&y);
    if(x == -1)
        AddToKernel(kernel, token, currentY, currentX);
}

void MainWindow::BuildKernel(QString key, QChar kernel [5][5])
{
    int keyLen = key.length();
    int currentX = 0;
    int currentY = 0;
    for(int i=0; i<keyLen;i++)
    {
        QChar token = key[i];
        CheckAddToKernel(&currentX, kernel, &currentY, token);
    }

    for(char ch = 'a'; ch<='z';  ch++)
    {
        if(ch != 'j')
            CheckAddToKernel(&currentX,kernel,&currentY,ch);
    }

    QString label = "";
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
            label += kernel[i][j] + ' '+' ';
        label += '\n';
    }
    ui->kernelLabel->setText(label);
}

void MainWindow::NormalizeString(QString* ptext)
{
    *ptext = ptext->toLower();
    for(int i=0; i<ptext->length(); i++)
        if((*ptext)[i]<'a' || (*ptext)[i]>'z')
        {
            *ptext = ptext->remove(i,1);
            i--;
        }
}

void MainWindow::FixDuplicateChar(QString* ptext)
{
    for(int i=0; i<ptext->length()-1; i++)
        if((*ptext)[i] == (*ptext)[i+1])
            *ptext = ptext->insert(i+1,'x');
}

void MainWindow::on_pushButton_clicked()
{    
    QString ptext = ui->plainText->toPlainText();
    QString key = ui->keyText->text();
    QString ctext = "";
    QChar kernel[5][5];

    NormalizeString(&ptext);    
    FixDuplicateChar(&ptext);
    NormalizeString(&key);
    BuildKernel(key, kernel);    


    int ptextLen = ptext.length();

    for(int i=0; i<ptextLen; i++)
    {
        QChar token1 = ptext[i];
        i++;
        QChar token2;
        if(i < ptextLen)
            token2 = ptext[i];
        else
            token2 = 'q';

        int x1,y1,x2,y2;
        FindInKernel(kernel, token1,&x1,&y1);
        FindInKernel(kernel, token2,&x2,&y2);
        if(x1 == x2)
        {
            y1 = (y1+1) % 5;
            y2 = (y2+1) % 5;
            ctext += kernel[y1][x1];
            ctext += kernel[y2][x2];
        }
        else if(y1 == y2)
        {
            x1 = (x1+1) % 5;
            x2 = (x2+1) % 5;
            ctext += kernel[y1][x1];
            ctext += kernel[y2][x2];
        }
        else
        {
            ctext += kernel[y1][x2];
            ctext += kernel[y2][x1];
        }
    }
    ui->cipherText->setPlainText(ctext);
}

void MainWindow::RemoveXForDuplicates(QString* ptext)
{
    for(int i=1; i<ptext->length()-1; i++)
        if((*ptext)[i]=='x' && (*ptext)[i-1] == (*ptext)[i+1])
            *ptext = ptext->remove(i,1);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString ctext = ui->cipherText2->toPlainText();
    QString key = ui->keyText->text();
    QString ptext = "";
    QChar kernel[5][5];

    ctext = ctext.replace('j','i');

    NormalizeString(&ctext);
    NormalizeString(&key);
    BuildKernel(key, kernel);
    int ctextLen = ctext.length();

    for(int i=0; i<ctextLen; i++)
    {
        QChar token1 = ctext[i];
        i++;
        QChar token2;
        if(i < ctextLen)
            token2 = ctext[i];
        else
            token2 = 'q';

        int x1,y1,x2,y2;
        FindInKernel(kernel, token1,&x1,&y1);
        FindInKernel(kernel, token2,&x2,&y2);
        if(x1 == x2)
        {
            y1 = (y1+4) % 5;
            y2 = (y2+4) % 5;
            ptext += kernel[y1][x1];
            ptext += kernel[y2][x2];
        }
        else if(y1 == y2)
        {
            x1 = (x1+4) % 5;
            x2 = (x2+4) % 5;
            ptext += kernel[y1][x1];
            ptext += kernel[y2][x2];
        }
        else
        {
            ptext += kernel[y1][x2];
            ptext += kernel[y2][x1];
        }
    }

    //RemoveXForDuplicates(&ptext);
    ui->plainText2->setPlainText(ptext);
}
