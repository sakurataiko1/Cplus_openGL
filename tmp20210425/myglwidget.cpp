// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    alpha = 25;
    beta = -25;
    distance = 2.5; //ズーム機能
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(640, 480);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}


//! [0]
void MyGLWidget::initializeGL()
{
    //! [0]
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    qglClearColor(QColor(Qt::black));

    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
    shaderProgram.link();

//    vertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) // Front
//             << QVector3D( 0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5)
//             << QVector3D( 0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) // Back
//             << QVector3D(-0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5)
//             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) // Left
//             << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
//             << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) // Right
//             << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5)
//             << QVector3D(-0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5, -0.5) // Top
//             << QVector3D( 0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5,  0.5)
//             << QVector3D(-0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5,  0.5) // Bottom
//             << QVector3D( 0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5, -0.5);
//
//    colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Front 赤
//           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
//           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Back　赤
//           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Left　緑
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right　緑
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Top　青
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1)
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom　青
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);

    //QVector(X,Y,Z) ←　openGL では(正面から見て) X:左右　Y：上下　Z:奥行。（手前＋、奥が- で通常の座標と違う）
    //↑　通常座標 (x, y, z)が入力されたら、openGL座標(X1, Y1, Z1) =  (x, z, -y) で代入することになる ※openGL座標は奥行Z1方向手前が+になるので -yにする
    vertices << QVector3D(-0.5, -0.9,  0.4) << QVector3D( 0.5, -0.9,  0.4) << QVector3D( 0.5,  0.9,  0.4) // Front
             << QVector3D( 0.5,  0.9,  0.4) << QVector3D(-0.5,  0.9,  0.4) << QVector3D(-0.5, -0.9,  0.4)
             << QVector3D( 0.5, -0.9, -0.4) << QVector3D(-0.5, -0.9, -0.4) << QVector3D(-0.5,  0.9, -0.4) // Back
             << QVector3D(-0.5,  0.9, -0.4) << QVector3D( 0.5,  0.9, -0.4) << QVector3D( 0.5, -0.9, -0.4)
             << QVector3D(-0.5, -0.9, -0.4) << QVector3D(-0.5, -0.9,  0.4) << QVector3D(-0.5,  0.9,  0.4) // Left
             << QVector3D(-0.5,  0.9,  0.4) << QVector3D(-0.5,  0.9, -0.4) << QVector3D(-0.5, -0.9, -0.4)
             << QVector3D( 0.5, -0.9,  0.4) << QVector3D( 0.5, -0.9, -0.4) << QVector3D( 0.5,  0.9, -0.4) // Right
             << QVector3D( 0.5,  0.9, -0.4) << QVector3D( 0.5,  0.9,  0.4) << QVector3D( 0.5, -0.9,  0.4)
             << QVector3D(-0.5,  0.9,  0.4) << QVector3D( 0.5,  0.9,  0.4) << QVector3D( 0.5,  0.9, -0.4) // Top
             << QVector3D( 0.5,  0.9, -0.4) << QVector3D(-0.5,  0.9, -0.4) << QVector3D(-0.5,  0.9,  0.4)
             << QVector3D(-0.5, -0.9, -0.4) << QVector3D( 0.5, -0.9, -0.4) << QVector3D( 0.5, -0.9,  0.4) // Bottom
             << QVector3D( 0.5, -0.9,  0.4) << QVector3D(-0.5, -0.9,  0.4) << QVector3D(-0.5, -0.9, -0.4);

    //! [1]
    colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Front 赤
           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
           << QVector3D(1, 0.5, 0.5) << QVector3D(1, 0.5, 0.5) << QVector3D(1, 0.5, 0.5) // Back　ピンク
           << QVector3D(1, 0.5, 0.5) << QVector3D(1, 0.5, 0.5) << QVector3D(1, 0.5, 0.5)
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Left　　緑
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
           << QVector3D(0.5, 1, 0.5) << QVector3D(0.5, 1, 0.5) << QVector3D(0.5, 1, 0.5) // Right　黄緑
           << QVector3D(0.5, 1, 0.5) << QVector3D(0.5, 1, 0.5) << QVector3D(0.5, 1, 0.5)
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Top　青
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1)
           << QVector3D(0.5, 0.5, 1) << QVector3D(0.5, 0.5, 1) << QVector3D(0.5, 0.5, 1) // Bottom　水色
           << QVector3D(0.5, 0.5, 1) << QVector3D(0.5, 0.5, 1) << QVector3D(0.5, 0.5, 1);


}
//! [1]

void MyGLWidget::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(0, 0, width, height);
}

//! [2]
void MyGLWidget::paintGL()
{
    //! [2]
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

    //! [3]
    shaderProgram.bind();

    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

    shaderProgram.setAttributeArray("vertex", vertices.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", colors.constData());
    shaderProgram.enableAttributeArray("color");

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    shaderProgram.disableAttributeArray("vertex");

    shaderProgram.disableAttributeArray("color");

    shaderProgram.release();
}
//! [3]

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();

    event->accept();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();

    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        if (beta < -90) {
            beta = -90;
        }
        if (beta > 90) {
            beta = 90;
        }

        updateGL();
    }

    lastMousePosition = event->pos();

    event->accept();
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }

        updateGL();
    }

    event->accept();
}
