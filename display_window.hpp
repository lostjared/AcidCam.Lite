#ifndef _DISPLAY_WINDOW_H_
#define _DISPLAY_WINDOW_H_

#include<QDialog>
#include<QWidget>
#include<vector>
#include<string>
#include<QTimer>
#include"acidcam/ac.h"

inline QImage Mat2QImage(cv::Mat const& src)
{
    cv::Mat temp;
    cvtColor(src, temp,cv::COLOR_BGR2RGB);
    QImage dest((const uchar *) temp.data, static_cast<int>(temp.cols), static_cast<int>(temp.rows), static_cast<int>(temp.step), QImage::Format_RGB888);
    dest.bits();
    return dest;
}

class AC_DisplayWindow : public QDialog {
    Q_OBJECT
public:
    AC_DisplayWindow(QWidget *parent = 0);
public slots:
    void update();
public:
    void setIndex(int index);
    bool loadList(QString lst);
    bool openCamera(int index, int w, int h);
    void paintEvent(QPaintEvent *p);
    void setDelay(int d);
private:
    std::vector<std::string> playback;
    int playback_index = 0;
    cv::VideoCapture cap;
    QTimer *timer;
    int delay = (24 * 30);
};


#endif