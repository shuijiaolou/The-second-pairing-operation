#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QIcon>
#include <stdlib.h>
#include <time.h>
/****
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

****/
//#include <QPrintDialog>
//#include <QPrinter>

#include <QFont>
#include <QFontDialog>
int flag_add=-1;
int flag_sub=-1;
int flag_mul=-1;
int flag_div=-1;
int flag_brackets=-1;
int flag_float=-1;
int num10=-1;
int num20=-1;
int num50=-1;
int num100=-1;
int number=10;
int Max=100;
int flag_max10=-1;
int flag_max50=-1;
int flag_max100=-1;
int flag_max1000=-1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(500,400);
    this->setWindowTitle("算式生成器");
    this->setWindowIcon(QIcon(":/images/file/notepad.png"));        //设置应用显示图标

    //实例菜单和控件
    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    mual_maxMenu = new QMenu(this);
    num_maxMenu = new QMenu(this);
    textEdit = new QTextEdit(this);
    vboxlayout = new QVBoxLayout(this);
    this->setCentralWidget(textEdit);


    //填充菜单子节点
    newAct = new QAction( tr( "新建" ), this );
    newAct->setShortcut(tr("Ctrl+N" ));        //快捷键
    newAct->setStatusTip(tr("新建文件" ));      //底部状态提示
    openAct = new QAction( tr( "打开" ), this );
    openAct->setShortcut(tr("Ctrl+O" ));
    openAct->setStatusTip(tr("打开文件" ));
    saveAct = new QAction(tr( "保存" ), this );
    saveAct->setShortcut(tr("Ctrl+S" ));
    saveAct->setStatusTip(tr("保存文件" ));
    saveasAct = new QAction( tr( "另存为" ), this );
    saveasAct->setShortcut(tr("Ctrl+Shift+S" ));
    saveasAct->setStatusTip(tr("另存为文件" ));
    runAct = new QAction(tr( "生成" ), this );
    runAct->setShortcut(tr("F5"));
    runAct->setStatusTip(tr("生成"));

    //信号与槽
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(saveasAct,SIGNAL(triggered()),this,SLOT(saveasFile()));

    addAct = new QAction( tr("加法" ), this );
    addAct->setStatusTip(tr("加法" ));
    addAct->setCheckable(true);

    subAct = new QAction(tr("减法" ), this );
    subAct->setStatusTip(tr("减法" ));
    subAct->setCheckable(true);


    mulAct = new QAction( tr("乘法" ), this );
    mulAct->setStatusTip(tr("乘法" ));
    mulAct->setCheckable(true);


    divAct = new QAction( tr("除法" ), this );
    divAct->setStatusTip(tr("除法" ));
    divAct->setCheckable(true);


    redoAct = new QAction( tr("括号" ), this );
    redoAct->setStatusTip(tr("括号" ));
    redoAct->setCheckable(true);


    floatAct = new QAction(tr("小数" ), this );
    floatAct->setStatusTip(tr("小数" ));
    floatAct->setCheckable(true);


    number10 = new QAction(tr("10" ), this );
    number10->setStatusTip(tr("生成10道计算题" ));
    number10->setCheckable(true);

    number20 = new QAction(tr("20" ), this );
    number20->setStatusTip(tr("生成20道计算题" ));
    number20->setCheckable(true);

    number50 = new QAction(tr("50" ), this );
    number50->setStatusTip(tr("生成50道计算题" ));
    number50->setCheckable(true);

    number100 = new QAction(tr("100" ), this );
    number100->setStatusTip(tr("生成100道计算题" ));
    number100->setCheckable(true);

    max10 = new QAction(tr("10" ), this );
    max10->setStatusTip(tr("生成数值<10" ));
    max10->setCheckable(true);

    max50 = new QAction(tr("50" ), this );
    max50->setStatusTip(tr("生成数值<50" ));
    max50->setCheckable(true);

    max100 = new QAction(tr("100" ), this );
    max100->setStatusTip(tr("生成数值<100" ));
    max100->setCheckable(true);

    max1000 = new QAction(tr("1000" ), this );
    max1000->setStatusTip(tr("生成数值<1000" ));
    max1000->setCheckable(true);

    //信号与槽
    connect(subAct, SIGNAL(triggered()), this, SLOT(subAction()));
    connect(addAct, SIGNAL(triggered()), this, SLOT(addAction()));
    connect(mulAct, SIGNAL(triggered()), this, SLOT(mulAction()));
    connect(divAct, SIGNAL(triggered()), this, SLOT(divAction()));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redoAction()));
    connect(floatAct, SIGNAL(triggered()), this, SLOT(floatAction()));
    connect(runAct, SIGNAL(triggered()), this, SLOT(runAction()));
    connect(number10, SIGNAL(triggered()), this, SLOT(subject_number10()));
    connect(number20, SIGNAL(triggered()), this, SLOT(subject_number20()));
    connect(number50, SIGNAL(triggered()), this, SLOT(subject_number50()));
    connect(number100, SIGNAL(triggered()), this, SLOT(subject_number100()));
    connect(max10, SIGNAL(triggered()), this, SLOT(max10Action()));
    connect(max50, SIGNAL(triggered()), this, SLOT(max50Action()));
    connect(max100, SIGNAL(triggered()), this, SLOT(max100Action()));
    connect(max1000, SIGNAL(triggered()), this, SLOT(max1000Action()));
    //填充菜单
    fileMenu = menuBar()->addMenu(tr( "文件" ));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addAction(runAct);
    fileMenu->addSeparator();

    editMenu = menuBar()->addMenu(tr("生成设置" ));
    editMenu->addAction(addAct);
    editMenu->addAction(subAct);
    editMenu->addAction(mulAct);
    editMenu->addAction(divAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(floatAct);
    menuBar()->addSeparator();

    mual_maxMenu = menuBar()->addMenu(tr("题目数量" ));
    mual_maxMenu->addAction(number10);
    mual_maxMenu->addAction(number20);
    mual_maxMenu->addAction(number50);
    mual_maxMenu->addAction(number100);

    num_maxMenu = menuBar()->addMenu(tr("取值范围" ));
    num_maxMenu->addAction(max10);
    num_maxMenu->addAction(max50);
    num_maxMenu->addAction(max100);
    num_maxMenu->addAction(max1000);
/*    //toolBar 工具条
    //fileTooBar添加
    fileToolBar = addToolBar(tr("新建"));     //右键添加改变
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveasAct);
    */
    //editToolBar添加
    editToolBar = addToolBar(tr("属性"));
    editToolBar->addAction(addAct);
    editToolBar->addAction(subAct);
    editToolBar->addAction(mulAct);
    editToolBar->addAction(divAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(floatAct);
    editToolBar->addAction(runAct);


}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::showMainwindow2()
{
    w2.show();
}
*/

/*槽函数实现*/

//子菜单事件
void MainWindow::newFile()
{
    /*
    QMessageBox::warning(this,tr("提示"),
    tr("创建新文件？"),
    QMessageBox::Yes | QMessageBox::Default,
    QMessageBox::No);
    */
    currentFile.clear();
    textEdit->setText(QString());
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    QFile file(fileName);
    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法打开文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    textEdit->setText(text);
    file.close();
}

void MainWindow::saveFile()
{
    QString fileName;
    // 若没有文件,重新创建一个
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "文件未保存: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::saveasFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "另存为");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "文件未保存: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::addAction()
{
    flag_add *= -1;

}

void MainWindow::subAction()
{
    flag_sub *= -1;
}

void MainWindow::mulAction()
{
    flag_mul *= -1;
}

void MainWindow::divAction()
{
    flag_div *= -1;
}

void MainWindow::redoAction()
{
    flag_brackets *= -1;
}
void MainWindow::max10Action()
{
    flag_max10 *= -1;
    if(flag_max10==1)
    {
        Max=10;
    }
}
void MainWindow::max50Action()
{
    flag_max50 *= -1;
    if(flag_max50==1)
    {
        Max=50;
    }
}
void MainWindow::max100Action()
{
    flag_max100 *= -1;
    if(flag_max100==1)
    {
        Max=100;
    }
}
void MainWindow::max1000Action()
{
    flag_max1000 *= -1;
    if(flag_max1000==1)
    {
        Max=1000;
    }
}
void MainWindow::subject_number10()
{
    num10 *= -1;
    if(num10==1)
    {
        number=10;
    }
}
void MainWindow::subject_number20()
{
    num20 *= -1;
    if(num20==1)
    {
        number=20;
    }
}
void MainWindow::subject_number50()
{
    num50 *= -1;
    if(num50==1)
    {
        number=50;
    }
}
void MainWindow::subject_number100()
{
    num100 *= -1;
    if(num100==1)
    {
        number=10;
    }
}
int randsymbol()
{
   int symbol=rand()%4;
   int i;
   int pass=0;
   int num[4]={-1,-1,-1,-1};
   if(flag_add==1)
   {
       num[0]=0;
   }
   if(flag_sub==1)
   {
       num[1]=1;
   }
   if(flag_mul==1)
   {
       num[2]=2;
   }
   if(flag_div==1)
   {
       num[3]=3;
   }
   for(i=0;i<4;i++)
   {
       if(symbol==num[i])
       {
           pass=1;
       }
   }
   if(pass==0)
   {
       symbol=randsymbol();
   }
   return symbol;
}
int seat_brackets(int x,int y)
{
    int goddess = rand()%2;
    int seat=0;
    if((x==0||x==1)&&(y==2||y==3))
    {
        if(goddess==1)
        {
            seat=1;
        }
    }
    else if((x==2||x==3)&&(y==0||y==1))
    {
        if(goddess==1)
        {
            seat=2;
        }
    }
    return seat;
}
void MainWindow::floatAction()
{
    flag_float *= -1;
}
void MainWindow::runAction()
{
    srand((unsigned)time(NULL));
    float x,y,z,m;
    int L1,L2,seat;
    QString character="+-*/";
    QString ch1,ch2;
    QString text[3];
    QString space="    ";
    for(int num=0;num<number/5;num++)
    {
        for(int i=0;i<3;i++)
        {
            x=rand()%Max;
            y=rand()%Max;
            z=rand()%Max;
            L1=randsymbol();
            L2=randsymbol();
            ch1= character[L1];
            ch2= character[L2];
            if(flag_float==1)
            {
                m=(float)(rand()%10)/10;
                x += m;
                m=(float)(rand()%10)/10;
                y += m;
                m=(float)(rand()%10)/10;
                z += m;
            }
            if(flag_brackets==1)
            {
                seat=seat_brackets(L1,L2);
            }
            if(seat==1)
            {
                text[i]=QString("(%1%2%3)%4%5=").arg(x).arg(ch1).arg(y).arg(ch2).arg(z);
            }
            else if(seat==2)
            {
                text[i]=QString("%1%2(%3%4%5)=").arg(x).arg(ch1).arg(y).arg(ch2).arg(z);
            }
            else{
                text[i]=QString("%1%2%3%4%5=").arg(x).arg(ch1).arg(y).arg(ch2).arg(z);
            }
            textEdit->insertPlainText(text[i]);
            textEdit->insertPlainText(space);
        }
            textEdit->insertPlainText("\n");
    }
}
