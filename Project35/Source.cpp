#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qApp->installEventFilter(this);
    ui->setupUi(this);
    setWindowTitle("Mouse Tracking v19.1");
    setFixedSize(900, 500);
    setMouseTracking(true);
    QFont LabelFont("Heivetica [Cronyx]", 24, QFont::Bold);
    QString LabelCss = "border-style: dashed;"
        "border-width: 1px;"
        "border-color: red;"
        "padding: 0;"
        "margin: 0";

    xMouseLabel = new QLabel("Mouse X:", this);
    xMouseLabel->setGeometry(0, 0, 600, 150);
    xMouseLabel->setFont(LabelFont);
    xMouseLabel->setStyleSheet(LabelCss);

    yMouseLabel = new QLabel("Mouse Y:", this);
    yMouseLabel->setGeometry(0, 150, 600, 150);
    yMouseLabel->setFont(LabelFont);
    yMouseLabel->setStyleSheet(LabelCss);

    trackingMouseLabel = new QLabel("Mouse tracking:", this);
    trackingMouseLabel->setGeometry(0, 300, 600, 150);
    trackingMouseLabel->setFont(LabelFont);
    trackingMouseLabel->setStyleSheet(LabelCss);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mouseMoveIvent(QMouseEvent* event) {
    xMouse = event->x();
    yMouse = event->y();
    qDebug() << "Mouse X: " << xMouse;
    qDebug() << "Mouse Y: " << yMouse;
    xMouseLabel->setText("Mouse x: " + QString("%1").arg(xMouse, 3, 14, QChar('0')));

}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        qDebug() << mouseEvent->pos().x();
        xMouse = mouseEvent->pos().x();
        yMouse = mouseEvent->pos().y();
        xMouseLabel->setText("Mouse X: " + QString("%1").arg(xMouse, 3, 10, QChar('0')));
        yMouseLabel->setText("Mouse Y: " + QString("%1").arg(yMouse, 3, 10, QChar('0')));
        trackingMouseLabel->setText("Mouse X: " + QString("%1 : %2").arg(xMouse, 3, 10, QChar('0')).arg(yMouse, 3, 10, QChar('0')));
    }
}

//mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    void mouseMoveIvent(QMouseEvent* event);
    int xMouse;
    int yMouse;
    QLabel* xMouseLabel;
    QLabel* yMouseLabel;
    QLabel* trackingMouseLabel;
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // MAINWINDOW_H
