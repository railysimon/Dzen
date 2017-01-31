#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QTimer>
#include <QVector>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <ctime>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
        QTimer *timer;

        QGraphicsScene *scene;
        QGraphicsView *view;

        int counter;
        void Creater();
        void Deleter();
        QVector<int> radiuses;
        QVector<QGraphicsEllipseItem*> ellipses;


private slots:
            void TimeSlot();

};

#endif // WINDOW_H
