#ifndef _DISPLAY_WINDOW_H_
#define _DISPLAY_WINDOW_H_

#include<QDialog>
#include<QWidget>

class AC_DisplayWindow : public QDialog {
    Q_OBJECT
public:
    AC_DisplayWindow(QWidget *parent = 0);
};


#endif