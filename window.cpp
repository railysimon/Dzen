#include "window.h"

Window::Window(QWidget *parent): QWidget(parent), counter(0)
{
    scene = new QGraphicsScene(QRectF(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()));
    view = new QGraphicsView(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer;
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeSlot()));
    timer->start();

    QMediaPlayer *player = new QMediaPlayer;
    QMediaPlaylist *list = new QMediaPlaylist(player);

    player->setPlaylist(list);
    list->addMedia(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/music.wav"));
    list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->play();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    this->setLayout(layout);
    this->setCursor(Qt::BlankCursor);
    this->showFullScreen();

}

Window::~Window()
{
}

void Window::Creater()
{
    radiuses.push_front(0);
    QGraphicsEllipseItem *temp = scene->addEllipse(0, 0, 0, 0);
    temp->setBrush(QBrush(QColor(rand() % 250, rand() % 250, rand() % 250), Qt::SolidPattern));
    ellipses.push_front(temp);
}

void Window::Deleter()
{
    radiuses.pop_back();
    QGraphicsEllipseItem *temp = ellipses.back();
    scene->removeItem(temp);
    ellipses.pop_back();
}

void Window::TimeSlot()
{
    if(counter == 100)
    {
        counter = 0;
        Creater();
    }

    if(!ellipses.isEmpty())
    {
        for(int i=0; i<ellipses.size(); i++)
        {
            ++radiuses[i];
            ellipses[i]->setRect(QApplication::desktop()->width()/2 - radiuses[i]/2,
                                 QApplication::desktop()->height()/2 - radiuses[i]/2, radiuses[i], radiuses[i]);
        }
    }

    if(!(radiuses.isEmpty()) && (radiuses[radiuses.size()-1] >= QApplication::desktop()->width() + 350)) Deleter();

    counter++;
}
