#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custombutton.h"

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

void MainWindow::openFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);

    QString fileContent = QString(file.readAll());
    QStringList rows = fileContent.split("\n");

    if (rows.length() <= 1) return; //Errormsg?

    this->currentScore = 0;
    this->possible_trials = this->trials = QString(rows.at(0)).replace(";","").toInt();

    this->ui->label_trials_total->setText(QString::number(trials));
    this->ui->label_trials_left->setText(QString::number(trials));
    this->ui->label_score_current->setText(QString::number(currentScore));


    for (int i = 1; i < rows.length(); i++)
    {
        if (rows.at(i).isEmpty())
            continue; //leere Zeilen überspringen
        QStringList cols = rows.at(i).split(";");
        for (int j = 0; j < cols.length(); j++)
        {
            CustomButton *btn = new CustomButton();
            btn->setData(i-1,j,cols.at(j).toInt());
            value_list.append(cols.at(j).toInt());
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(btn_clicked()));
            this->ui->field->addWidget(btn, i-1,j);
            buttons.append(btn);
        }
    }


    std::sort(value_list.begin(), value_list.end());
    this->maxPossibleScore = value_list.last();

    /*
    for (int i = value_list.length()-1; i >= value_list.length()-this->possible_trials; i--)
        this->maxPossibleScore += value_list.at(i);
    */
    this->ui->label_score_max->setText(QString::number(this->maxPossibleScore));
}

void MainWindow::on_action_ffnen_triggered()
{
    //Restore
    this->on_actionFeld_l_schen_triggered();

    QString filePath = QFileDialog::getOpenFileName(this, "Datei auswählen", QDir::homePath(), "*.csv");
    if (filePath.isEmpty()) return;

    this->openFile(filePath);

}

void MainWindow::on_actionFeld_l_schen_triggered()
{
    for (int i = 0; i < buttons.length(); i++)
    {
        this->ui->field->removeWidget(buttons.at(i));
        delete buttons.at(i);
    }
    buttons.clear();
    value_list.clear();
}

void MainWindow::btn_clicked()
{
    CustomButton *btn = (CustomButton*)sender();
    if (btn == 0) return; //

    int x = btn->getx();
    int y = btn->gety();
    int var = btn->getvar();
    QLabel *l = new QLabel(QString::number(var));
    l->setAlignment(Qt::AlignCenter);

    l->setMinimumSize(btn->size());
    l->setMaximumSize(btn->size());

    buttons.removeAll(btn);
    buttons.append(l);
    btn->deleteLater();
    this->ui->field->addWidget(l,x,y);
    this->trials--;
    this->currentScore = qMax(var, this->currentScore);
    this->ui->label_trials_left->setText(QString::number(this->trials));
    this->ui->label_score_current->setText(QString::number(this->currentScore));

    if (this->trials == 0)
    {
        QMessageBox::information(this, "Spiel beendet", QString("Sie haben %1 von %2 möglichen Punkten erreicht").arg(this->currentScore).arg(this->maxPossibleScore));
        this->on_actionFeld_l_schen_triggered();
    }
}

void MainWindow::on_action_triggered()
{
    QMessageBox::about(this, "Über dieses Programm", "Johannes Winkler\nInstitut für Statistik\nAlpen-Adria Universität Klagenfurt\nhttp://stat.aau.at");
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls())
    {
        const QString &filename = url.toLocalFile();
        this->openFile(filename);
        break; //first one
    }
}
