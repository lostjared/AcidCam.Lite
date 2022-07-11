#include"main_window.hpp"
#include<QLabel>
#include<QFileDialog>

AC_MainWindow::AC_MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("AcidCam.Lite");
    setFixedSize(290, 180);

    QLabel *lbl = new QLabel(this);
    lbl->setText("Playback: ");
    lbl->setGeometry(25, 50, 75, 20);
    list_filename = new QLineEdit(this);
    list_filename->setGeometry(100, 50, 100, 25);
    list_open = new QPushButton(tr("Open"), this);
    list_open->setGeometry(210, 50, 50, 25);

    connect(list_open, SIGNAL(clicked()), this, SLOT(selectList()));

    start_program = new QPushButton(tr("Start"), this);
    start_program->setGeometry(25, 110, 100, 25);

    connect(start_program, SIGNAL(clicked()), this, SLOT(startProgram()));

}

void AC_MainWindow::selectList() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Images (*.key)"));
    if(fileName.length() > 0) {
        list_filename->setText(fileName);
    }
}

void AC_MainWindow::startProgram() {

}