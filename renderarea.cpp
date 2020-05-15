#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <math.h>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor (0,0,255),
    mShapeColor  (255,255,255),
    mShape(Asteroid)
{
    on_shape_changed();
}

void RenderArea::on_shape_changed () {

    switch (mShape) {
        case Asteroid:
            mScale = 40;
            mIntervalLength = 2*M_PI;
            mStepcount = 256;
            break;
        case Cycloid:
            break;
        case HuygensCycloid:
            break;
        case HypoCycloid:
            break;
        default:
            break;

    }
}

QPointF RenderArea::compute_asteroid (float t) {
    float cos_t = cos (t);
    float sint_t = sin (t);
    float x = 2*cos_t*cos_t*cos_t;
    float y = 2*sint_t*sint_t*sint_t;
    return QPointF(x,y);

}

QSize RenderArea:: minimumSizeHint() const
{
    return QSize(100,100);
}
QSize RenderArea::sizeHint() const  {
    return QSize(400,200);
}

void RenderArea::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);


    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);


    //drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();
    float step = mIntervalLength/mStepcount;
    for (float t=0;t<mIntervalLength;t +=step)
    {
            QPointF point = compute_asteroid(t);
            QPoint pixel;
            pixel.setX(point.x()*mScale + center.x());
            pixel.setY(point.y()*mScale + center.y());

            painter.drawPoint(pixel);

    }
}
