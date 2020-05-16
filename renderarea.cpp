#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <math.h>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor (0,0,255),
    mPen(Qt::white),
    mShape(Asteroid)
{
    mPen.setWidth(2);
    on_shape_changed();
}

void RenderArea::on_shape_changed () {

    switch (mShape) {
        case Asteroid:
            mScale = 90;
            mIntervalLength = 2*M_PI;
            mStepcount = 256;
            break;
        case Cycloid:
            mScale = 10;
            mIntervalLength = 4*M_PI;
            mStepcount = 128;
            break;
        case HuygensCycloid:
            mScale = 12;
            mIntervalLength = 4*M_PI;
            mStepcount = 256;
            break;
        case HypoCycloid:
            mScale = 40;
            mIntervalLength = 2*M_PI;
            mStepcount = 256;
            break;
        case Line:
            mScale = 100;
            mIntervalLength = 2;
            mStepcount = 128;
            break;
        case Circle:
            mScale = 165;
            mIntervalLength = 2*M_PI;
            mStepcount = 128;
        case Ellipse:
            mScale = 75;
            mIntervalLength = 2*M_PI;
            mStepcount = 128;
        case Fancy:
            mScale = 10;
            mIntervalLength = 12*M_PI;
            mStepcount = 512;
        case Star:
            mScale = 25;
            mIntervalLength = 6*M_PI;
            mStepcount = 256;
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

QPointF RenderArea::compute_fancy (float t){
    return QPointF (11.0f *cos(t) - 6*((11/6) *t),11.0f *sin(t) - 6*sin((11/6)*t));


}

QPointF RenderArea::compute_star (float t){
    return QPointF (2*cos(t) + 5*cos((t*2)/3),
                    2*sin(t) - 5*sin((t*2)/3)
               );

}


QPointF RenderArea:: compute (float t) {

    switch (mShape) {
        case Asteroid:
            return compute_asteroid(t);
            break;
        case Cycloid:
            return compute_cycloid(t);
            break;
        case HuygensCycloid:
            return compute_huygens(t);
            break;
        case HypoCycloid:
            return compute_hypo(t);
            break;
        case Line:
            return compute_line(t);
            break;
        case Circle:
            return compute_circle(t);
            break;
        case Ellipse:
            return compute_ellipse(t);
            break;
        case Fancy:
            return compute_fancy(t);
            break;
         case Star:
            return compute_star(t);
            break;
        default:
            break;

    }
    return QPointF(0,0);
}


QPointF RenderArea::compute_circle (float t) {

    return QPointF(cos(t),sin(t));

}

QPointF RenderArea:: compute_ellipse(float t){

    return QPointF(2*cos(t),(1.1)*sin(t));
}


QPointF RenderArea:: compute_line (float t) {

    return QPointF(1-t,1-t);
}

QPointF RenderArea:: compute_cycloid (float t) {
    return QPointF(
                1.5*(1-cos(t)),
                1.5*(t-sin(t))
                );
}

QPointF RenderArea:: compute_huygens (float t) {
    return QPoint(4*(3*cos(t) -cos(3*t)),
                  4*(3*sin(t) - sin(3*t)));


}

QPointF RenderArea:: compute_hypo (float t) {
    return QPoint(
            1.5*(2*cos(t) + cos(2*t)),
            1.5*(2*sin(t) - sin(2*t))
                );
}



QSize RenderArea:: minimumSizeHint() const
{
    return QSize(400,400);
}
QSize RenderArea::sizeHint() const  {
    return QSize(400,400);
}

void RenderArea::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);


    painter.setBrush(mBackgroundColor);
    painter.setPen(mPen);


    //drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();
    QPointF prevPoint = compute(0);
    QPoint prevPixel;
            prevPixel.setX(prevPoint.x()*mScale + center.x());
            prevPixel.setY(prevPoint.y()*mScale + center.y());
    float step = mIntervalLength/mStepcount;
    for (float t=0;t<mIntervalLength;t +=step)
    {
            QPointF point = compute(t);
            QPoint pixel;
            pixel.setX(point.x()*mScale + center.x());
            pixel.setY(point.y()*mScale + center.y());

           painter.drawLine(pixel,prevPixel);
           prevPixel = pixel;

    }
    QPointF point = compute(mIntervalLength);
    QPoint pixel;
    pixel.setX(point.x()*mScale + center.x());
    pixel.setY(point.y()*mScale + center.y());

   painter.drawLine(pixel,prevPixel);
   prevPixel = pixel;

}
