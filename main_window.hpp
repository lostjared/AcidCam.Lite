#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include<QMainWindow>
#include<QWidget>
#include<QLineEdit>
#include<QPushButton>

class AC_MainWindow : public QMainWindow {
    Q_OBJECT
public:
    AC_MainWindow(QWidget *parent = 0);

private:
    QLineEdit *list_filename;
    QPushButton *list_open;
};

#endif