#include "ponggame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PongGame pong;
    pong.show();

    return a.exec();
}
