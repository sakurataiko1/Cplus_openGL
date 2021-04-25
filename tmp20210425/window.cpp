//#include "window.h"
//#include "ui_window.h"

//Window::Window(QWidget *parent)
//    : QWidget(parent)
//    , ui(new Ui::Window)
//{
//    ui->setupUi(this);
//}

//Window::~Window()
//{
//    delete ui;
//}

// window.cpp

#include <QtWidgets>
#include "window.h"
#include "ui_window.h"

#include "myglwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->myGLWidget, SIGNAL(xRotationChanged(int)), ui->rotXSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(yRotationChanged(int)), ui->rotYSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(zRotationChanged(int)), ui->rotZSlider, SLOT(setValue(int)));

    ui->rotXSlider->setVisible(false);//[DEBUG]    一時的に非表示
    ui->rotYSlider->setVisible(false);//[DEBUG]    一時的に非表示
    ui->rotZSlider->setVisible(false);//[DEBUG]    一時的に非表示

    ui->tableWidget_material->setColumnCount(3);
    QStringList labels;

    labels << "check" << "No" << "material";
    ui->tableWidget_material->setHorizontalHeaderLabels(labels);
    ui->tableWidget_material->QTableWidget::horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_material->setEditTriggers(QAbstractItemView::NoEditTriggers); //Tablel状の値の直接編集禁止
    ui->tableWidget_material->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_material->setColumnWidth(0,40);
    ui->tableWidget_material->setColumnWidth(1,80);

    ui->tableWidget_material->insertRow(0);
    ui->tableWidget_material->setItem(0,0, new QTableWidgetItem("_"));
    ui->tableWidget_material->setItem(0,1, new QTableWidgetItem("Air"));
    ui->tableWidget_material->setItem(0,2, new QTableWidgetItem("0"));
}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}


