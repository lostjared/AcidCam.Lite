#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include<QMainWindow>
#include<QWidget>

class AC_MainWindow : public QMainWindow {
    Q_OBJECT
public:
    AC_MainWindow(QWidget *parent = 0);
};

#endif