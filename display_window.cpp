#include"display_window.hpp"
#include"acidcam/ac.h"
#include<fstream>

AC_DisplayWindow::AC_DisplayWindow(QWidget *parent) : QDialog(parent) {

}

void AC_DisplayWindow::update() {

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

    return true;
}