#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
public:
    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Asteroid,Cycloid,HuygensCycloid,HypoCycloid};

    void setBackgroundColor(QColor color) {
        mBackgroundColor = color;
    }
    QColor backgroundColor () const {return mBackgroundColor;}

    void setShape (ShapeType shape) {mShape = shape; on_shape_changed();}
    ShapeType shape () const {return mShape;}

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

private:
    void on_shape_changed();
    QPointF compute_asteroid(float t);

private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;
    float mIntervalLength;
    float mScale;
    int mStepcount;


};

#endif // RENDERAREA_H
