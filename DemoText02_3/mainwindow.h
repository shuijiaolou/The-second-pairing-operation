#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>

#include <mainwindow2.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainWindow2 w2;
    QString currentFile;

private:

    //新建
    QMenu *fileMenu, *editMenu, *mual_maxMenu,*num_maxMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;        //新建两个工具栏，用以存放四个菜单动作
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveasAct;
    QAction *addAct;
    QAction *subAct;
    QAction *mulAct;
    QAction *divAct;
    QAction *redoAct;
    QAction *floatAct;
    QAction *number10;
    QAction *number20;
    QAction *number50;
    QAction *number100;
    QAction *max10;
    QAction *max50;
    QAction *max100;
    QAction *max1000;
    QAction *runAct;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QVBoxLayout *vboxlayout;

private slots:
    //void showMainwindow2();
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void addAction();
    void subAction();
    void mulAction();
    void divAction();
    void redoAction();
    void runAction();
    void subject_number10();
    void subject_number20();
    void subject_number50();
    void subject_number100();
    void floatAction();
    void max10Action();
    void max50Action();
    void max100Action();
    void max1000Action();
};

#endif // MAINWINDOW_H
