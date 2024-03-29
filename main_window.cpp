#include"main_window.hpp"
#include<QLabel>
#include<QFileDialog>
#include"display_window.hpp"
#include<QMessageBox>
#include<QMenuBar>


AC_MainWindow::AC_MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("AcidCam.Lite");
    setFixedSize(290, 190);

    QLabel *lbl = new QLabel(this);
    lbl->setText("Playback: ");
    lbl->setGeometry(25, 50, 75, 20);
    list_filename = new QLineEdit(this);
    list_filename->setGeometry(100, 50, 100, 25);
    list_open = new QPushButton(tr("Open"), this);
    list_open->setGeometry(210, 50, 50, 25);

    connect(list_open, SIGNAL(clicked()), this, SLOT(selectList()));


    QLabel *ilbl = new QLabel(tr("Delay: "), this);
    ilbl->setGeometry(25, 130, 100, 25);

    input_delay = new QLineEdit("30", this);
    input_delay->setGeometry(180, 130, 100, 25);

    start_program = new QPushButton(tr("Start"), this);
    start_program->setGeometry(25, 160, 100, 25);

    connect(start_program, SIGNAL(clicked()), this, SLOT(startProgram()));

    display_window = new AC_DisplayWindow(this);
    display_window->hide();
    display_window->setIndex(0);

    camera_index = new QLineEdit("0", this);
    QLabel *lblx = new QLabel(tr("Camera: "), this);
    lblx->setGeometry(25, 85, 80, 25);
    camera_index->setGeometry(180, 85, 100, 25);

    shuffle_box = new QCheckBox(tr("Shuffle"), this);
    shuffle_box->setGeometry(135, 160, 100, 25);

    help_menu = menuBar()->addMenu(tr("Help"));

    help_about = new QAction(tr("About"));
    
    connect(help_about, SIGNAL(triggered()), this, SLOT(displayAbout()));

    help_menu->addAction(help_about);

    file_menu = menuBar()->addMenu(tr("File"));
    file_exit = new QAction(tr("Exit"));
    connect(file_exit, SIGNAL(triggered()), this, SLOT(exitProgram()));


}

void AC_MainWindow::selectList() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Images (*.key)"));
    if(fileName.length() > 0) {
        list_filename->setText(fileName);
    }
}

void AC_MainWindow::startProgram() {
    if(mode_start == false) {
        int num = atoi(camera_index->text().toStdString().c_str());
        int delay = atoi(input_delay->text().toStdString().c_str());
        if(list_filename->text().length() > 0 && num >= 0) {
            display_window->setIndex(0);
            if(!display_window->loadList(list_filename->text())) {
                QMessageBox::information(this, tr("Error opening playback list"), tr("Error opening playback list"));
                return;           
            }

            if(shuffle_box->isChecked()) {
                display_window->setShuffle(true);
                display_window->shuffleList();
            }
            else 
                display_window->setShuffle(false);

            if(!display_window->openCamera(num, 1280, 720)) {
                QMessageBox::information(this, tr("Could not start camera. Wrong camera device?"), tr("Could not start camera, wrong device indeX?"));
                return;
            }
            display_window->setDelay(delay);
            display_window->show();
            mode_start = true;
            start_program->setText(tr("Stop"));
        }
    } else {
        mode_start = false;
        start_program->setText(tr("Start"));
        display_window->stop();
    }
}

void AC_MainWindow::displayAbout() {
    QMessageBox::information(this, tr("AcidCam.Lite by LostSideDead Software\nhttp://lostsidedead.com"), tr("AcidCam.Lite by LostSideDead Software\nhttp://lostsidedead.com"));
}

void AC_MainWindow::exitProgram() {
    display_window->stop();
    exit(0);
}