#include"main_window.hpp"
#include<QLabel>

AC_MainWindow::AC_MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("AcidCam.Lite");
    setFixedSize(800, 600);


    QLabel *lbl = new QLabel(this);
    lbl->setText("Playback: ");
    lbl->setGeometry(25, 50, 75, 20);
    list_filename = new QLineEdit(this);
    list_filename->setGeometry(100, 50, 100, 20);


}
