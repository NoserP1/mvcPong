#ifndef PONGVIEW_H
#define PONGVIEW_H

#include <memory>
#include <QWidget>
#include "pongmodel.h"

class PongView :public QWidget
{
public:
    PongView(std::shared_ptr<const PongModel> pongModel, QWidget * parent = 0);
    ~PongView();

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    std::shared_ptr<const PongModel> _pongModel;
    float            _normFactor;
};

#endif // PONGVIEW_H
