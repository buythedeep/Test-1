#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);

    QString title(tr("This is Note app"));
    setWindowTitle(title);

    connect(ui->actionFont, &QAction::triggered, this, &MainWindow::selectFont);
    connect(ui->actionBold, &QAction::triggered, this, &MainWindow::setFontBold);
    connect(ui->actionUnderline, &QAction::triggered, this, &MainWindow::setFontUnderline);
    connect(ui->actionItalic, &QAction::triggered, this, &MainWindow::setFontItalic);

/*
    QFileSystemModel* model = new QFileSystemModel(this);
    model->setRootPath("./");
    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->index("./"));
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    current_file.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString note_file_name = QFileDialog::getOpenFileName(this, "Open note");
    current_file = note_file_name;
    QFile file(note_file_name);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Notice", "file didn't open");
    }
    QTextStream in(&file);
    //QString note_text = &file.readAll();
    QString note_text = in.readAll();
    ui->textEdit->setText(note_text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString note_file_name = QFileDialog::getSaveFileName(this, "Save...");
    QFile file(note_file_name);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Notice", "file didn't save");
    }
    current_file = note_file_name;
    QTextStream out(&file);
    QString note_text = ui->textEdit->toPlainText();
    out << note_text;
    file.close();
/*
    mynotice_j.insert(QDateTime::currentDateTime().toString("'note_'yyyy_MM_dd_HH_mm_ss'"), QJsonValue::fromVariant(note_text));
    QJsonDocument doc(mynotice_j);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    QFile file_j;
    file_j.setFileName(QDateTime::currentDateTime().toString("'note_'yyyy_MM_dd_HH_mm_ss'.json'"));
    file_j.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream( &file_j );
    stream << jsonString;
    file_j.close();
*/
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::setFontBold(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
           ui->textEdit->setFontWeight(QFont::Normal);
}

void MainWindow::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void MainWindow::setFontUnderline(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

void MainWindow::setFontItalic(bool italic)
{
    ui->textEdit->setFontItalic(italic);
}

/*
void MainWindow::on_listView_clicked(const QModelIndex &index)
{

}
*/
