#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>

#include <QDropEvent>
#include <QMimeData>

#include "custombutton.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openFile(QString filePath);

private slots:
    void on_action_ffnen_triggered();
    void on_actionFeld_l_schen_triggered();
    void btn_clicked();

    void on_action_triggered();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);


private:
    Ui::MainWindow *ui;
    int trials;
    int possible_trials;
    QList< QWidget*> buttons;
    QList <int> value_list;
    int currentScore;
    int maxPossibleScore;

};

#endif // MAINWINDOW_H
