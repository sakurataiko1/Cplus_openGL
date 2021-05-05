#include "myfunction.h"


myfunction::myfunction(QWidget *parent) : QWidget(parent)
{

}

myfunction::~myfunction(){

}

QVector3D myfunction::func_defineColor(int input_colornum){
     QVector3D resultColor = QVector3D(1, 0, 0);
     int tmpint_color = input_colornum % 10;

     if(tmpint_color == 0){ resultColor = QVector3D(1, 0, 0); } //赤
     if(tmpint_color == 1){ resultColor = QVector3D(0, 1, 0); } //緑
     if(tmpint_color == 2){ resultColor = QVector3D(0, 0, 1); } //青

     if(tmpint_color == 3){ resultColor = QVector3D(1, 1, 0); }
     if(tmpint_color == 4){ resultColor = QVector3D(1, 0, 1); }

     if(tmpint_color == 5){ resultColor = QVector3D(1, 1, 0); }
     if(tmpint_color == 6){ resultColor = QVector3D(0, 1, 1); }

     if(tmpint_color == 7){ resultColor = QVector3D(1, 0, 1); }
     if(tmpint_color == 8){ resultColor = QVector3D(0, 1, 1); }

     if(tmpint_color == 9){ resultColor = QVector3D(1.0, 0.5, 0.0); }
     if(tmpint_color == 10){ resultColor = QVector3D(1.0, 0.5, 0.5); }
     if(tmpint_color == 11){ resultColor =  QVector3D(0.5, 1.0, 0.0); }
     if(tmpint_color == 12){ resultColor =  QVector3D(0.5, 1.0, 0.5); }
     if(tmpint_color == 13){ resultColor =  QVector3D(0.5, 0.0, 1.0); }
     if(tmpint_color == 14){ resultColor =  QVector3D(0.5, 0.5, 1.0); }
     if(tmpint_color == 15){ resultColor =  QVector3D(0.7, 0.0, 1.0); }

     return resultColor;

}
