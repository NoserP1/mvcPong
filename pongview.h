#ifndef PONGVIEW_H
#define PONGVIEW_H

#include <QWidget>
#include "pongmodel.h"

class PongView :public QWidget
{
public:
    PongView(const PongModel* pongModel, QWidget * parent = 0);
    ~PongView();

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    const PongModel* _pongModel;
    float            _normFactor;
};

#endif // PONGVIEW_H
