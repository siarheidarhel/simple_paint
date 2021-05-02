#include "myscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QPen>
#include <QGraphicsLineItem>
#include <QtMath>
#include <QPainter>
#include <QPicture>

MyScene::MyScene(QObject *parent):QGraphicsScene(parent)
{
}


void MyScene::setFigureType(int figureType)
{
    figureType_=figureType;
}



void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event==nullptr) return;
    start_point = event->scenePos();



}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
         Q_UNUSED(event)
        if(!figure)return;
        saveContainer_.push_back(figure);
        figure=nullptr;


}




void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if(event==nullptr) return;

  end_point =event->scenePos();

  if(figureType_ == Line) drawLine();

  if(figureType_==Rectangle) drawRect();

 if(figureType_==Triangle) drawTriangle();

 if(figureType_== Pencil) drawPencile();

 if(figureType_==Circle) drawCircle();

 if(figureType_==Points) drawPoints();



}


void MyScene::drawLine()
{
    if(figure)
    {
        delete figure;
        figure =nullptr;
    }
    figure =  addLine(start_point.x(), start_point.y(),end_point.x(), end_point.y(),QPen(myPen));
}



void MyScene::drawRect(){

    if(figure){delete figure;}


 QRectF rect ( end_point.x() > start_point.x() ? start_point.x() : start_point.x(),
                    end_point.y() > start_point.y() ? start_point.y() : end_point.y(),
                    qAbs(end_point.x() - start_point.x()),
                    qAbs(end_point.y() - start_point.y()));


    figure= addRect(rect,QPen(myPen),QBrush(myBrush));


}

void MyScene::drawTriangle(){

   if(figure){delete figure;}

 QPolygonF triangle;

        triangle << QPointF(start_point.x() + (end_point.x() > start_point.x() ? + 1 : - 1)*
                               abs((end_point.x() - start_point.x())/2), start_point.y())
                    << QPointF((end_point.x() > start_point.x()) ? end_point.x() : start_point.x(),
                               end_point.y())
                    << QPointF((end_point.x() > start_point.x()) ? start_point.x() : end_point.x(),
                               end_point.y());


      figure = addPolygon(triangle,QPen(myPen),QBrush(myBrush));


}



void MyScene::clearScene(){
    QGraphicsScene::clear();
    saveContainer_.clear();
    update();
}


void MyScene::drawPencile(){

   // start_point=end_point
    figure =  addLine(start_point.x(), start_point.y(),end_point.x(), end_point.y(),QPen(myPen));
    start_point=end_point;
}


void MyScene::drawCircle(){
    if(figure){delete figure;}

    auto w=end_point.x()-start_point.x();
    auto h=end_point.y()-start_point.y();

    figure= addEllipse(start_point.x(), start_point.y(),w, h,QPen(myPen),QBrush(myBrush));

}

void MyScene::drawPoints(){
    if(figure){delete figure;}

    figure = addEllipse(end_point.x(),end_point.y(),4,4,QPen(Qt::black),QBrush("black"));
}


void MyScene::undoMethod(){

    this->removeItem(saveContainer_.pop());



}

void MyScene::colourDial(QColor colour){

    myPen.setColor(colour);


}

void MyScene::setLineWidth(int lineWidth){

    myPen.setWidth(lineWidth);
}



void MyScene::setFillColour(QColor colourFill){

    myBrush.setStyle(Qt::SolidPattern);
    myBrush.setColor(colourFill);
}

void MyScene::saveOption(){



}

