#include"display_window.hpp"
#include"ac.h"
#include<fstream>
#include<QPainter>
#include<QKeyEvent>
#include<algorithm>

AC_DisplayWindow::AC_DisplayWindow(QWidget *parent) : QDialog(parent) {
    ac::init();
    setWindowTitle("AcidCam Lite - Playback");
}

void AC_DisplayWindow::update() {

    static int frame_counter = 0;
    if(++frame_counter > delay) {
        setIndex(playback_index+1);
        frame_counter = 0;
    }

    repaint();
}

void AC_DisplayWindow::shuffleList() {
    if(shuffle_on == true) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle (playback.begin(), playback.end(), std::default_random_engine(seed));
    }
}

void AC_DisplayWindow::setIndex(int index) {
    playback_index = index;
    if(playback_index > static_cast<int>(playback.size()-1)) {
        playback_index = 0;
        shuffleList();
    }
}

void AC_DisplayWindow::setShuffle(bool s) {
    shuffle_on = s;
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
        if(file) {
            if(std::find(ac::solo_filter.begin(), ac::solo_filter.end(), s) != ac::solo_filter.end())
                playback.push_back(s);
            else
                std::cerr << "ac-lite: Filter " << s << " not found!.\n";
        }
    }
    file.close();
    return true;
}

void AC_DisplayWindow::keyPressEvent(QKeyEvent *ke) {
    if(ke->key() == Qt::Key_Escape) {
        exit(0);
    }
    if(ke->key() == Qt::Key_F)
        showFullScreen();
    if(ke->key() == Qt::Key_D)
        showNormal();
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
        int wx = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int hx = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        this->setGeometry(0, 0, wx, hx);
        cv::Mat m;
        cap.read(m);
        if(shuffle_on)
            shuffleList();
        timer = new QTimer(this);
        timer->setInterval(1000/24/8);
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
        ac::CallFilter(playback.at(playback_index), m);
        QImage img;
        img = Mat2QImage(m);
        painter.fillRect(QRect(0, 0, width(), height()), QBrush("#000000"));
        painter.drawImage(QRect(0, 0, width(), height()), img);
        QFont font = painter.font();
        QPen pen = painter.pen();
        pen.setColor(QColor(QRgb(0xFF0000)));
        font.setPixelSize(30);
        font.setBold(true);
        painter.setPen(pen);
        painter.setFont(font);
        painter.drawText(25, 25, playback.at(playback_index).c_str());
    }
}

void AC_DisplayWindow::setDelay(int d) {
    if(delay > 24) {
        delay = d * static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    }
}

void AC_DisplayWindow::stop() {
    timer->stop();
    cap.release();
    hide();
}
