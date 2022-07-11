#ifndef _DISPLAY_WINDOW_H_
#define _DISPLAY_WINDOW_H_

#include<QDialog>
#include<QWidget>
#include<vector>
#include<string>

class AC_DisplayWindow : public QDialog {
    Q_OBJECT
public:
    AC_DisplayWindow(QWidget *parent = 0);
    void update();
    void setIndex(int index);
    bool loadList(QString lst);
    bool openCamera(int index, int w, int h);
private:
    std::vector<std::string> playback;
    int playback_index = 0;
};


#endif