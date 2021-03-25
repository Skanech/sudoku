#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    int a,b,i,j,x,y,x1,y1,x2,y2,l1,l2,ch1=0,ch2=0;
    bool fl=0;
    for (int i=0;i<9;i++)
    {
        for (int j=0;j<9;j++)
        {
            if (ui->tableWidget->item(i,j)!=nullptr)
                ui->tableWidget->item(i,j)->text().toInt(&fl);
            else
            {
                fl=false;
                QTableWidgetItem * ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            if (fl)
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::green);
            else
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::yellow);
        }
    }
    for (i=0;i<9;i++) //по горизонтали
    {
        for (j=0;j<9;j++)
        {
            if (ui->tableWidget->item(i,j)->text().toInt()!=0)
            {
                for (x=0;x<9;x++)
                {
                    for (y=0;y<9;y++)
                    {
                        if (ui->tableWidget->item(x,y)->text().toInt()!=0 && x!=i && y!=j)
                        {
                            if (ui->tableWidget->item(i,j)->text().toInt()==ui->tableWidget->item(x,y)->text().toInt())
                            {
                                if (x-i<3 && x-i>0)
                                {
                                    if ((x==6 && i==7) || (x==7 && i==6))
                                        a=8;
                                    else if ((x==6 && i==8) || (x==8 && i==6))
                                        a=7;
                                    else if ((x==7 && i==8) || (x==8 && i==7))
                                        a=6;
                                    else if ((x==3 && i==4) || (x==4 && i==3))
                                        a=5;
                                    else if ((x==3 && i==5) || (x==5 && i==3))
                                        a=4;
                                    else if ((x==5 && i==4) || (x==4 && i==5))
                                        a=3;
                                    else if ((x==0 && i==1) || (x==1 && i==0))
                                        a=2;
                                    else if ((x==0 && i==2) || (x==2 && i==0))
                                        a=1;
                                    else if ((x==1 && i==2) || (x==2 && i==1))
                                        a=0;
                                    else
                                        a=-1;
                                    if (a!=-1)
                                    {
                                        int n=0;
                                        if (i==0 || i==3 || i==6)   //проверка на наличие проверяемого значения
                                        {
                                            for (int m=0;m<3;m++)
                                            {
                                                for (int k=0;k<9;k++)
                                                {
                                                    if (ui->tableWidget->item(i+m,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                        n++;
                                                }
                                            }
                                        }
                                        else if (i==1 || i==4 || i==7)
                                        {
                                            for (int m=-1;m<2;m++)
                                            {
                                                for (int k=0;k<9;k++)
                                                {
                                                    if (ui->tableWidget->item(i+m,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                        n++;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            for (int m=-2;m<1;m++)
                                            {
                                                for (int k=0;k<9;k++)
                                                {
                                                    if (ui->tableWidget->item(i+m,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                        n++;
                                                }
                                            }
                                        }

                                        if ((j==0 || j==1 || j==2 || y==0 || y==1 || y==2) && (y==3 || y==4 || y==5 || j==3 || j==4 || j==5) && n<3)    //изначальные элементы в первом и втором квадрате
                                        {
                                            l1=0;l2=0;
                                            for (b=6;b<9;b++)
                                            {
                                                for (int k=0;k<9;k++)   //проверка на наличие элемента под возможными местами вставки
                                                {
                                                    if (ui->tableWidget->item(k,b)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                    {
                                                        l1++;
                                                        ch1=b;
                                                    }
                                                }   //проверка на свободные места
                                                if (ui->tableWidget->item(a,b)->text().toInt()!=0)
                                                {
                                                    l2++;
                                                    ch2=b;
                                                }
                                            }
                                            if ((l1==1 && l2==1 && ch1!=ch2) || l1==2 || l2==2)
                                            {
                                                for (b=6;b<9;b++)
                                                {
                                                    if (ui->tableWidget->item(a,b)->text().toInt()!=0);
                                                    else
                                                    {
                                                        fl=false;
                                                        for (int k=0;k<9;k++)   //проверка на наличие элемента под возможными местами вставки для вставки
                                                        {
                                                            if (ui->tableWidget->item(k,b)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                                fl=true;
                                                        }
                                                        if (fl==false)
                                                        {
                                                            QTableWidgetItem* item = new QTableWidgetItem;
                                                            item->setText(QString::number(ui->tableWidget->item(i,j)->text().toInt()));
                                                            ui->tableWidget->setItem(a,b,item);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if ((j==0 || j==1 || j==2 || y==0 || y==1 || y==2) && (y==6 || y==7 || y==8 || j==6 || j==7 || j==8) && n<3)    //изначальные элементы в первом и третьем квадрате
                                        {
                                            l1=0;l2=0;
                                            for (b=3;b<6;b++)
                                            {
                                                for (int k=0;k<9;k++)   //проверка на наличие элемента под возможными местами вставки
                                                {
                                                    if (ui->tableWidget->item(k,b)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                    {
                                                        l1++;
                                                        ch1=b;
                                                    }
                                                }   //проверка на свободные места
                                                if (ui->tableWidget->item(a,b)->text().toInt()!=0)
                                                {
                                                    l2++;
                                                    ch2=b;
                                                }
                                            }
                                            if ((l1==1 && l2==1 && ch1!=ch2) || l1==2 || l2==2)
                                            {
                                                for (b=3;b<6;b++)
                                                {
                                                    if (ui->tableWidget->item(a,b)->text().toInt()!=0);
                                                    else
                                                    {
                                                        fl=false;
                                                        for (int k=0;k<9;k++)
                                                        {
                                                            if (ui->tableWidget->item(k,b)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                                fl=true;
                                                        }
                                                        if (fl==false)
                                                        {
                                                            QTableWidgetItem* item = new QTableWidgetItem;
                                                            item->setText(QString::number(ui->tableWidget->item(i,j)->text().toInt()));
                                                            ui->tableWidget->setItem(a,b,item);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if ((j==3 || j==4 || j==5 || y==3 || y==4 || y==5) && (y==6 || y==7 || y==8 || j==6 || j==7 || j==8) && n<3)    //изначальные элементы во втором и третьем квадрате
                                        {
                                            l1=0;l2=0;
                                            for (b=0;b<3;b++)
                                            {
                                                for (int k=0;k<9;k++)   //проверка на наличие элемента под возможными местами вставки
                                                {
                                                    if (ui->tableWidget->item(k,b)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                    {
                                                        l1++;
                                                        ch1=b;
                                                    }
                                                }   //проверка на свободные места
                                                if (ui->tableWidget->item(a,b)->text().toInt()!=0)
                                                {
                                                    l2++;
                                                    ch2=b;
                                                }
                                            }
                                            if ((l1==1 && l2==1 && ch1!=ch2) || l1==2 || l2==2)
                                            {
                                                for (b=0;b<3;b++)
                                                {
                                                    if (ui->tableWidget->item(a,b)->text().toInt()!=0);
                                                    else
                                                    {
                                                        fl=false;
                                                        for (int k=0;k<9;k++)
                                                        {
                                                            if (ui->tableWidget->item(k,b)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                                fl=true;
                                                        }
                                                        if (fl==false)
                                                        {
                                                            QTableWidgetItem* item = new QTableWidgetItem;
                                                            item->setText(QString::number(ui->tableWidget->item(i,j)->text().toInt()));
                                                            ui->tableWidget->setItem(a,b,item);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (i=0;i<9;i++) //по вертикали
    {
        for (j=0;j<9;j++)
        {
            if (ui->tableWidget->item(i,j)->text().toInt()!=0)
            {
                for (x=0;x<9;x++)
                {
                    for (y=0;y<9;y++)
                    {
                        if (ui->tableWidget->item(x,y)->text().toInt()!=0 && x!=i && y!=j)
                        {
                            if (ui->tableWidget->item(i,j)->text().toInt()==ui->tableWidget->item(x,y)->text().toInt())
                            {
                                if (y-j<3 && y-j>0)
                                {
                                    if ((y==6 && j==7) || (y==7 && j==6))
                                        b=8;
                                    else if ((y==6 && j==8) || (y==8 && j==6))
                                        b=7;
                                    else if ((y==7 && j==8) || (y==8 && j==7))
                                        b=6;
                                    else if ((y==3 && j==4) || (y==4 && j==3))
                                        b=5;
                                    else if ((y==3 && j==5) || (y==5 && j==3))
                                        b=4;
                                    else if ((y==5 && j==4) || (y==4 && j==5))
                                        b=3;
                                    else if ((y==0 && j==1) || (y==1 && j==0))
                                        b=2;
                                    else if ((y==0 && j==2) || (y==2 && j==0))
                                        b=1;
                                    else if ((y==1 && j==2) || (y==2 && j==1))
                                        b=0;
                                    else
                                        b=-1;
                                    if (b!=-1)
                                    {
                                        int n=0;
                                        if (j==0 || j==3 || j==6)   //проверка на наличие проверяемого значения
                                        {
                                            for (int m=0;m<3;m++)
                                            {
                                                for (int k=0;k<9;k++)
                                                {
                                                    if (ui->tableWidget->item(k,j+m)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                        n++;
                                                }
                                            }
                                        }
                                        else if (j==1 || j==4 || j==7)
                                        {
                                            for (int m=-1;m<2;m++)
                                            {
                                                for (int k=0;k<9;k++)
                                                {
                                                    if (ui->tableWidget->item(k,j+m)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                        n++;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            for (int m=-2;m<1;m++)
                                            {
                                                for (int k=0;k<9;k++)
                                                {
                                                    if (ui->tableWidget->item(k,j+m)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                        n++;
                                                }
                                            }
                                        }

                                        if ((i==0 || i==1 || i==2 || x==0 || x==1 || x==2) && (x==3 || x==4 || x==5 || i==3 || i==4 || i==5) && n<3)    //изначальные элементы в первом и втором квадрате
                                        {
                                            l1=0;l2=0;
                                            for (a=6;a<9;a++)
                                            {
                                                for (int k=0;k<9;k++)   //проверка на наличие элемента по горизонтали возможных мест для вставки
                                                {
                                                    if (ui->tableWidget->item(a,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                    {
                                                        l1++;
                                                        ch1=a;
                                                    }
                                                }   //проверка на свободные места
                                                if (ui->tableWidget->item(a,b)->text().toInt()!=0)
                                                {
                                                    l2++;
                                                    ch2=a;
                                                }
                                            }
                                            if ((l1==1 && l2==1 && ch1!=ch2) || l1==2 || l2==2)
                                            {
                                                for (a=6;a<9;a++)
                                                {
                                                    if (ui->tableWidget->item(a,b)->text().toInt()!=0);
                                                    else
                                                    {
                                                        fl=false;
                                                        for (int k=0;k<9;k++)   //проверка на наличие элемента под возможными местами вставки для вставки
                                                        {
                                                            if (ui->tableWidget->item(a,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                                fl=true;
                                                        }
                                                        if (fl==false)
                                                        {
                                                            QTableWidgetItem* item = new QTableWidgetItem;
                                                            item->setText(QString::number(ui->tableWidget->item(i,j)->text().toInt()));
                                                            ui->tableWidget->setItem(a,b,item);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if ((i==0 || i==1 || i==2 || x==0 || x==1 || x==2) && (x==6 || x==7 || x==8 || x==6 || x==7 || x==8) && n<3)    //изначальные элементы в первом и третьем квадрате
                                        {
                                            l1=0;l2=0;
                                            for (a=3;a<6;a++)
                                            {
                                                for (int k=0;k<9;k++)   //проверка на наличие элемента под возможными местами вставки
                                                {
                                                    if (ui->tableWidget->item(a,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                    {
                                                        l1++;
                                                        ch1=a;
                                                    }
                                                }   //проверка на свободные места
                                                if (ui->tableWidget->item(a,b)->text().toInt()!=0)
                                                {
                                                    l2++;
                                                    ch2=a;
                                                }
                                            }
                                            if ((l1==1 && l2==1 && ch1!=ch2) || l1==2 || l2==2)
                                            {
                                                for (a=3;a<6;a++)
                                                {
                                                    if (ui->tableWidget->item(a,b)->text().toInt()!=0);
                                                    else
                                                    {
                                                        fl=false;
                                                        for (int k=0;k<9;k++)
                                                        {
                                                            if (ui->tableWidget->item(a,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                                fl=true;
                                                        }
                                                        if (fl==false)
                                                        {
                                                            QTableWidgetItem* item = new QTableWidgetItem;
                                                            item->setText(QString::number(ui->tableWidget->item(i,j)->text().toInt()));
                                                            ui->tableWidget->setItem(a,b,item);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if ((i==3 || i==4 || i==5 || x==3 || x==4 || x==5) && (x==6 || x==7 || x==8 || i==6 || x==7 || x==8) && n<3)    //изначальные элементы во втором и третьем квадрате
                                        {
                                            l1=0;l2=0;
                                            for (a=0;a<3;a++)
                                            {
                                                for (int k=0;k<9;k++)   //проверка на наличие элемента под возможными местами вставки
                                                {
                                                    if (ui->tableWidget->item(a,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                    {
                                                        l1++;
                                                        ch1=a;
                                                    }
                                                }   //проверка на свободные места
                                                if (ui->tableWidget->item(a,b)->text().toInt()!=0)
                                                {
                                                    l2++;
                                                    ch2=a;
                                                }
                                            }
                                            if ((l1==1 && l2==1 && ch1!=ch2) || l1==2 || l2==2)
                                            {
                                                for (a=0;a<3;a++)
                                                {
                                                    if (ui->tableWidget->item(a,b)->text().toInt()!=0);
                                                    else
                                                    {
                                                        fl=false;
                                                        for (int k=0;k<9;k++)
                                                        {
                                                            if (ui->tableWidget->item(a,k)->text().toInt()==ui->tableWidget->item(i,j)->text().toInt())
                                                                fl=true;
                                                        }
                                                        if (fl==false)
                                                        {
                                                            QTableWidgetItem* item = new QTableWidgetItem;
                                                            item->setText(QString::number(ui->tableWidget->item(i,j)->text().toInt()));
                                                            ui->tableWidget->setItem(a,b,item);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (i=0;i<3;i++) //свободный элемент в первом квадрате
    {
        for (j=0;j<3;j++)
        {
            if (ui->tableWidget->item(i,j)->text().toInt()==0)
            {
                for (int m=1;m<10;m++)
                {
                    for (a=0;a<3;a++)   //проверка на наличие элемента в первом квадрате
                    {
                        for (b=0;b<3;b++)
                        {
                            if (ui->tableWidget->item(a,b)->text().toInt()==m)
                            {
                                m++;
                            }
                        }
                    }
                    for (x1=3;x1<9;x1++)
                    {
                        for (y1=0;y1<3;y1++)
                        {
                            for (x2=0;x2<3;x2++)
                            {
                                for (y2=3;y2<9;y2++)
                                {
                                    if (ui->tableWidget->item(x1,y1)->text().toInt()==m && ui->tableWidget->item(x2,y2)->text().toInt()==m)  //первый квадрат
                                    {
                                        int n=0;
                                        l1=0;
                                        for (a=0;a<3;a++)
                                        {
                                            for (b=0;b<3;b++)
                                            {
                                                if (ui->tableWidget->item(a,b)->text().toInt()==m)
                                                    l1=1;
                                                if (a!=x1 && a!=x2 && b!=y1 && b!=y2 && ui->tableWidget->item(a,b)->text().toInt()==0)
                                                {
                                                    n++;
                                                    i=a;
                                                    j=b;
                                                }
                                            }
                                        }
                                        if (n==1 && l1==0)
                                        {
                                            QTableWidgetItem* item = new QTableWidgetItem;
                                            item->setText(QString::number(m));
                                            ui->tableWidget->setItem(i,j,item);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Widget::on_pushButton_2_clicked()
{
    for (int i=0;i<9;i++)
    {
        for (int j=0;j<9;j++)
        {
            ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
        }
    }
    ui->tableWidget->clear();
}
