#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include<QTimer>
#include<QDateTime>
#include<QDebug>
#include<QLCDNumber>
#include<QFile>
#include<QIODevice>
#include<QTextStream>

QString door,lcd1,lcd2,hs,ms,sec,ahs,ams,asec,sr;
int counter=00,cm=0,ss,mm,pre,s1,s2,sflag=0,sp;
int d1,d2=0,e1,e2,flag=0,si,mi,hi,sf,mf,min,scs,ascs,asf,dr=0,i=0,ssi,mmi,hhi;

QFile file("/home/ubuntu/QT_PROJECTS/uv_light/snrval");
QFile addfile("/home/ubuntu/QT_PROJECTS/uv_light/addval");
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd("/home/ubuntu/QT_PROJECTS/uv_light/b1.jpeg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

    timer=new QTimer(this);
    objTimer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(my_tfunction()));


    connect (objTimer, SIGNAL (timeout()), this, SLOT (on_start_clicked()));


    timer->start(1000);
    ui->f->display("00");
    ui->f_3->display(":");
    ui->f_2->display("00");
    ui->mstatus->setText("OFF STATE");
    ui->label_doorstatus->setText("DOOR IS OPEND");
   // loadvalues();
    addloadvalues();
    on_Door_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::my_tfunction()
{

    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    QString date=QDate::currentDate().toString();

    if((time.second()%2)==0)
    {
        time_text[3]=' ';
        time_text[8]=' ';


    }
    ui->Date_time->setText(time_text);

   ui->date->setText(date);

}
void MainWindow::loadvalues()
{
    if(file.open(QIODevice::ReadWrite))
    {

    QTextStream in(&file);
    sec=in.readLine();
    ms=in.readLine();
    hs=in.readLine();

    ui->lcdNumber_sec->display(sec);
    ui->lcdNumber_min->display(ms);
    ui->lcdNumber_hr->display(hs);

    si=sec.toInt();
    mi=ms.toInt();
    hi=hs.toInt();


    }
    else
    {
        qDebug()<<"f not open"<<endl;
    }
    file.close();
}
void MainWindow::addloadvalues()
{
    if(addfile.open(QIODevice::ReadOnly))
    {

    QTextStream inn(&addfile);
    asec=inn.readLine();
    ams=inn.readLine();
    ahs=inn.readLine();


    ssi=asec.toInt();
    mmi=ams.toInt();
    hhi=ahs.toInt();
    ui->lcdNumber_sec->display(ssi);
    ui->lcdNumber_min->display(mmi);
    ui->lcdNumber_hr->display(hhi);


    }
    else
    {
        qDebug()<<"f not open"<<endl;
    }
    addfile.close();
}
void MainWindow::insertvalues()
{
    ascs=e1+ssi;
    if(ascs>59)
    {
        asf=ascs-60;
        mmi+=1;
    }
    else
       {
       asf=ssi+e1;

       }

 mmi+=e2;
if(e2>59)
{
  e2=0;
  hhi++;

}

    addfile.open(QIODevice::WriteOnly);
    QTextStream out(&addfile);
    out<<asf<<endl;
    out<<mmi<<endl;
    out<<hhi<<endl;

ui->lcdNumber_sec->display(QString::number(asf));
ui->lcdNumber_min->display(QString::number(mmi));
ui->lcdNumber_hr->display(QString::number(hhi));

    addfile.close();
}
void MainWindow::secvalue()
{

    if(si)
    {
        if(d1>si)
        {
            scs=d1-si;
            sf=60-scs;
            d2+=1;
        }

      else
      {
        sf=si-d1;
      }
  }
    else
    {
        sf=60-d1;
        d2+=1;
    }
ui->lcdNumber_sec->display(QString::number(sf));

}
void MainWindow::minvalue()
{
    if(mi)
    {
        if(d2>mi)
        {
            min=d2-mi;
            mf=60-min;
            hi-=1;
        }

    else
    {
        mf=mi-d2;
    }
   }
    else
    {
        mf=min-d2;
        hi-=1;
    }


    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    in<<sf<<endl;
    in<<mf<<endl;
    in<<hi<<endl;
    file.close();
    ui->lcdNumber_min->display(QString::number(mf));
    ui->lcdNumber_hr->display(QString::number(hi));
}
void MainWindow::updateProgressBar()
{

    progress = new QTimer(this);
    connect(progress, SIGNAL (on_start_clicked()), ui->progressBar, SLOT(setValue(int)));


    progress->start(1000);

   ui->progressBar->setValue(i--);
   qDebug()<<"i pi val="<<i<<endl;


}

void MainWindow::on_Door_clicked()
{
            objTimer->stop();
            ui->start->setDisabled(true);
            ui->start->setText("");
            ui->push_reset->setDisabled(true);
            ui->push_reset->setText("");
            //ui->push_reset->setStyleSheet("bagroundcolor:white");
            ui->minus->setDisabled(true);
            ui->minus->setText("");
            //ui->minus->setStyleSheet("bagroundcolor:white");
            ui->plus->setDisabled(true);
            ui->plus->setText("");
            ui->label_doorstatus->setText("DOOR IS OPEN");
            ui->mstatus->setText("OFF STATE");


}



void MainWindow::on_start_clicked()
{
    updateProgressBar();
     ui->mstatus->setText("RUNNING..");
     ui->start->setDisabled(true);
     ui->plus->setDisabled(true);
     ui->minus->setDisabled(true);
         objTimer->start(1000);
         if(cm!=0)
         {
          counter--;
          qDebug()<<"min co val="<<counter;
          ui->f->display(counter);
          if(counter<0)
          {
              counter=59;
              ui->f->display(counter);

              cm-=1;
              qDebug()<<"cm val="<<cm;
              ui->f_2->display(cm);
          }
        }
         if(cm==0 && counter>=0)
         {

             qDebug()<<"min co val="<<counter;
             ui->f->display(counter);
             counter-=1;
         }
         if(cm==0 && counter==-1)
         {
                   counter++;
                    objTimer->stop();
                        ui->start->setDisabled(false);
                        ui->plus->setDisabled(false);
                        ui->minus->setDisabled(false);
                        ui->mstatus->setText("OFF STATE");
                    ui->f->display("00");
                    ui->f_2->display("00");
                   // loadvalues();
                    //secvalue();
                    //minvalue();
                    addloadvalues();
                    insertvalues();


         }

}

void MainWindow::on_plus_clicked()
{



}

void MainWindow::on_minus_clicked()
{
    i--;
    ui->progressBar->setMaximum(i);
    qDebug()<<"i min val="<<i<<endl;
    if(flag)
    {
   if(cm!=0)
   {
    counter--;

    ui->f->display(counter);
    if(counter<0)
    {
        counter=59;
        ui->f->display(counter);

        cm-=1;

        ui->f_2->display(cm);
    }
  }
   if(cm==0 && counter>=0)
   {


       ui->f->display(counter);
       counter-=1;
   }
   if(cm==0 && counter==-1)
   {
             counter++;
   }

}
}

void MainWindow::on_Door_toggled(bool checked)
{

}

void MainWindow::on_Door_clicked(bool checked)
{



}

void MainWindow::on_Door_close_clicked()
{


            ui->start->setDisabled(false);
            ui->start->setText("START");
            ui->push_reset->setDisabled(false);
            ui->push_reset->setText("RESRT");
            ui->minus->setDisabled(false);
            ui->minus->setText("-");
            ui->plus->setDisabled(false);
            ui->plus->setText("+");
            ui->label_doorstatus->setText("DOOR IS CLOSED");


}

void MainWindow::on_pushButton_skip_clicked()
{

}

void MainWindow::on_plus_pressed()
{
    flag=1;
    if(sflag){i=0;sflag=0;}
    if(counter>=59)
    {
        qDebug()<<"co val="<<counter;
        counter=0;
        ui->f->display("00");
        cm+=1;
        ui->f_2->display(cm);
     }
    else
    {
        counter++;
       this->ui->f->display(counter);
        qDebug()<<"co val="<<counter;
    }


    i++;
    ui->progressBar->setMaximum(i);

    d1=ui->f->value();

    d2=ui->f_2->value();

    e1=d1;
    e2=d2;


}

void MainWindow::on_push_reset_clicked()
{

    counter=0;
    i=0;
    objTimer->stop();
    ui->progressBar->setValue(0);
    progress->stop();

    ui->f->display("00");
    ui->f_2->display("00");
    ui->start->setDisabled(false);
    ui->plus->setDisabled(false);
    ui->minus->setDisabled(false);
    ui->mstatus->setText("OFF STATE");
}

void MainWindow::on_push_skip_clicked()
{

    ui->progressBar->setValue(0);
    progress->stop();
    objTimer->stop();
     pre=counter;
     counter=0;
     s1=0;
     s2=0;
     s1=ui->f->value();
     d1-=s1;
     e1=d1;
     s2=ui->f_2->value();
     d2-=s2;
     e2=d2;
     ui->f->display("00");
     ui->f_2->display("00");
    // loadvalues();
     //secvalue();
     //minvalue();
     addloadvalues();
     insertvalues();
     ui->start->setDisabled(false);
     ui->plus->setDisabled(false);
     ui->minus->setDisabled(false);
     ui->mstatus->setText("OFF STATE");
     sflag=1;

}

void MainWindow::on_push_preload_clicked()
{   if(sflag)
    {

    d1=s1;
    d2=s2;
    if(d1==0 && d2==0)
    {
    ui->f->display("00");
    ui->f_2->display("00");
    }
    else
     {
        ui->f->display(d1);
        ui->f_2->display(d2);

    }
    counter=pre;
    ui->progressBar->setMaximum(i);
    sflag=0;
    }
}

void MainWindow::on_pushButton_sensor_clicked()
{
   file.open(QIODevice::ReadOnly);
   QTextStream ss(&file);
    sr=ss.readLine();

     sp=sr.toInt();
     if(sp==1)
   {
             ui->start->setDisabled(false);
             ui->start->setText("START");
             ui->push_reset->setDisabled(false);
             ui->push_reset->setText("RESRT");
             ui->minus->setDisabled(false);
             ui->minus->setText("-");
             ui->plus->setDisabled(false);
             ui->plus->setText("+");
             ui->label_doorstatus->setText("DOOR IS CLOSED");

   }


     file.close();
}
