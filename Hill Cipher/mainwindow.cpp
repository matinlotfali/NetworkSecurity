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

int MainWindow::mod(int a, int b)
{
   while(a<0)
       a += b;
   while(a>=b)
       a -= b;
   return a;
}

int MainWindow::modInv(int a, int b)
{
    for(int i=0; i<=25; i++)
        if(mod(a*i,b)==1)
            return i;
    return -1;
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

QString MainWindow::Encrypt(int matrix[2][2], QString ptext)
{
    NormalizeString(&ptext);

    QString ctext = "";
    int ptextLen = ptext.length();
    for(int i=0; i<ptextLen;i++)
    {
        ushort p1 = (ptext[i]).unicode()-97;
        i++;
        QChar token2;
        if(i < ptextLen)
            token2 = ptext[i];
        else
            token2 = 'q';
        ushort p2 = (token2).unicode()-97;
        int c1 = mod(p1*matrix[0][0]+p2*matrix[1][0],26);
        int c2 = mod(p1*matrix[0][1]+p2*matrix[1][1],26);
        ctext += (c1+97);
        ctext += (c2+97);
    }

    return ctext;
}

void MainWindow::on_pushButton_clicked()
{
    int matrix[2][2];
    matrix[0][0] = ui->a11->value();
    matrix[0][1] = ui->a12->value();
    matrix[1][0] = ui->a21->value();
    matrix[1][1] = ui->a22->value();

    QString ptext = ui->plainText->toPlainText();
    QString ctext = Encrypt(matrix, ptext);

    ui->cipherText->setPlainText(ctext);
}

QString MainWindow::BuildInvKey(int key[2][2], int akey[2][2])
{
    int det = key[0][0]*key[1][1]-key[1][0]*key[0][1];
    QString r = "det = " + QString::number(det);
    det = mod(det,26);
    r += "\ndet mod 26 = " + QString::number(det);
    det = modInv(det,26);
    r += "\ndet^-1 mod 26 = " + QString::number(det);

    int amatrix[2][2];
    amatrix[0][0] = key[1][1];
    amatrix[0][1] = -key[0][1];
    amatrix[1][0] = -key[1][0];
    amatrix[1][1] = key[0][0];

    akey[0][0] = mod(det*amatrix[0][0],26);
    akey[0][1] = mod(det*amatrix[0][1],26);
    akey[1][0] = mod(det*amatrix[1][0],26);
    akey[1][1] = mod(det*amatrix[1][1],26);

    r+= "\n\nKey^-1 = "+QString::number(det)+"*\t"+QString::number(amatrix[0][0])+"\t"+QString::number(amatrix[0][1])+"\t\t"+QString::number(akey[0][0])+"\t"+QString::number(akey[0][1]);
    r+= "\n\t\t"+QString::number(amatrix[1][0])+"\t"+QString::number(amatrix[1][1])+" mod 26 = \t"+QString::number(akey[1][0])+"\t"+QString::number(akey[1][1]);
    return r;
}

void MainWindow::on_pushButton_2_clicked()
{
    int key[2][2];
    key[0][0] = ui->a11->value();
    key[0][1] = ui->a12->value();
    key[1][0] = ui->a21->value();
    key[1][1] = ui->a22->value();

    int ikey[2][2];
    QString r = BuildInvKey(key,ikey);

    ui->reportLabel->setText(r);

    QString ctext = ui->cipherText2->toPlainText();
    QString ptext = Encrypt(ikey, ctext);

    ui->plainText2->setPlainText(ptext);
}
