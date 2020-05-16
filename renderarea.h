#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
public:
    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Asteroid,Cycloid,HuygensCycloid,HypoCycloid,Line,Circle,Ellipse,Fancy,Star};

    void setBackgroundColor(QColor color) {
        mBackgroundColor = color;
    }
    QColor backgroundColor () const {return mBackgroundColor;}

    void setShapeColor (QColor color) {mPen.setColor(color);}
    QColor shapeColor() const {return mPen.color();}

    void setScale (float scale) {
        mScale = scale;
        repaint();
    }
    float scale () const {return  mScale;}

    void setInterval (float length) {
        mIntervalLength = length;
        repaint();
    }
    float intervalLength () const {return  mIntervalLength;}

    void setStepCount (int count) {mStepcount = count;repaint();}
    int stepCount() const {return mStepcount;}


    void setShape (ShapeType shape) {mShape = shape; on_shape_changed();}
    ShapeType shape () const {return mShape;}

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

private:
    void on_shape_changed();
    QPointF compute_asteroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QPointF compute(float t);
    QPointF compute_line(float t);
    QPointF compute_circle(float t);
    QPointF compute_ellipse(float t);

    QPointF compute_fancy(float t);
    QPointF compute_star(float t);


private:
    QColor mBackgroundColor;
    ShapeType mShape;
    QPen mPen;
    float mIntervalLength;
    float mScale;
    int mStepcount;


};

#endif // RENDERAREA_H
