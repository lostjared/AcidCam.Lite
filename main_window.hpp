#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include<QMainWindow>
#include<QWidget>
#include<QLineEdit>
#include<QPushButton>

class AC_DisplayWindow;

class AC_MainWindow : public QMainWindow {
    Q_OBJECT
public:
    AC_MainWindow(QWidget *parent = 0);

public slots:
    void selectList();
    void startProgram();
private:
    QLineEdit *list_filename;
    QPushButton *list_open;
    QPushButton *start_program;
    AC_DisplayWindow *display_window;
};

#endif