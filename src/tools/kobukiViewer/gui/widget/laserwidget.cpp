#include "laserwidget.h"

LaserWidget::LaserWidget()
{

    setAutoFillBackground(true);

    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);

    setMaximumSize(500, 500);
    setMinimumSize(500, 500);


    setWindowTitle("Laser");
}

void LaserWidget::update(JdeRobotTypes::LaserData laserData)
{
    mutex.lock();

    this->laserData = laserData;
    QWidget::update();

    mutex.unlock();

}

void LaserWidget::paintEvent(QPaintEvent *)
{
    int _width = width();
    int _height = height();

    //center of laser
    int cx = _width/2;
    int cy = _height/2; 

    float x0, y0, x1, y1, d, ang;

    int width = 2;
    QPen pen;

    QPainter painter(this);
    painter.setPen(pen);

    pen = QPen(Qt::blue, width);
    painter.setPen(pen);

    if (this->laserData.values.size() > 0){

        float step = (this->laserData.maxAngle - this->laserData.minAngle) /this->laserData.values.size();

        d = this->laserData.maxRange/(_width/2); //normalizing distances 


        ang = this->laserData.minAngle;
        x0 = cx + (this->laserData.values[0] / d) * cos(ang);
        y0 = cy - ((this->laserData.values[0] / d) * sin(ang));

        for (int i = 1; i < this->laserData.values.size(); i++) {

        
            ang = this->laserData.minAngle + i*step;
            x1 = cx + (this->laserData.values[i] / d) * cos(ang);
            y1 = cy - ((this->laserData.values[i] / d) * sin(ang));


            painter.drawLine(QPointF(x0,y0), QPointF(x1,y1));

            x0 = x1;
            y0 = y1;

        }
    }
}


