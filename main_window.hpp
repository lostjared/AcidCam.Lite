#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_
#define VERSION_INFO "v0.1"
#include<QMainWindow>
#include<QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QCheckBox>

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
    QLineEdit *camera_index;
    QPushButton *list_open;
    QPushButton *start_program;
    QLineEdit *input_delay;
    QCheckBox *shuffle_box;
    AC_DisplayWindow *display_window;
    bool mode_start = false;
};

#endif