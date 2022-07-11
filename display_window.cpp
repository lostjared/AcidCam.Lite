#include"display_window.hpp"
#include"acidcam/ac.h"
#include<fstream>
#include<QPainter>

AC_DisplayWindow::AC_DisplayWindow(QWidget *parent) : QDialog(parent) {
    ac::init();
}

void AC_DisplayWindow::update() {
    repaint();
}

void AC_DisplayWindow::setIndex(int index) {
    playback_index = index;
}

bool AC_DisplayWindow::loadList(QString lst) {
    std::fstream file;
    file.open(lst.toStdString(), std::ios::in);

    if(!file.is_open())
        return false;

    if(!playback.empty())
        playback.erase(playback.begin(), playback.end());

    while(!file.eof()) {
        std::string s;
        std::getline(file, s);
        if(file) 
            playback.push_back(s);
    }
    file.close();
    return true;
}

bool AC_DisplayWindow::openCamera(int index, int w, int h) {
#ifdef _WIN32
    cap.open(index, cv::CAP_DSHOW);
#else
    cap.open(index);
#endif
    if(cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, w);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, h);
        cap.set(cv::CAP_PROP_FPS, 24);
        this->setGeometry(0, 0, w, h);
        timer = new QTimer(this);
        timer->setInterval(1000/24/2);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start();
        return true;
    }
    return false;
}

void AC_DisplayWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    cv::Mat m;
    if(cap.read(m)) {
        // display m
        // update counters
        QImage img;
        img = Mat2QImage(m);
        painter.fillRect(QRect(0, 0, width(), height()), QBrush("#000000"));
        painter.drawImage(QRect(0, 0, width(), height()), img);
    }

}