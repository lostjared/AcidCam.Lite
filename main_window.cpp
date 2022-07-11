#include"main_window.hpp"
#include<QLabel>

AC_MainWindow::AC_MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("AcidCam.Lite");
    setFixedSize(400, 600);

    QLabel *lbl = new QLabel(this);
    lbl->setText("Playback: ");
    lbl->setGeometry(25, 50, 75, 20);
    list_filename = new QLineEdit(this);
    list_filename->setGeometry(100, 50, 100, 25);
    list_open = new QPushButton(tr("Open"), this);
    list_open->setGeometry(210, 50, 50, 25);

    connect(list_open, SIGNAL(clicked()), this, SLOT(selectList()));
}

void AC_MainWindow::selectList() {

}