#include "qobj3dviewer.h"
#include <QDebug>

QObj3dViewer::QObj3dViewer(QWidget *parent) : QOpenGLWidget(parent)
{
    texture = Q_NULLPTR;
}

QObj3dViewer::~QObj3dViewer()
{
    if(texture != Q_NULLPTR)
        delete texture;
}

void QObj3dViewer::setTriangles(QVector<QOpenGLTriangle3D> &_triangles)
{
    triangles.clear();
    normals.clear();

    for(int i=0; i<_triangles.count(); i++)
    {
        triangles.append(_triangles.at(i).p1);
        triangles.append(_triangles.at(i).p2);
        triangles.append(_triangles.at(i).p3);

        normals.append(_triangles.at(i).p1Normal);
        normals.append(_triangles.at(i).p2Normal);
        normals.append(_triangles.at(i).p3Normal);

        textureUV.append(_triangles.at(i).p1UV);
        textureUV.append(_triangles.at(i).p2UV);
        textureUV.append(_triangles.at(i).p3UV);
    }

    update();
}

void QObj3dViewer::initializeGL()
{
    initializeOpenGLFunctions();

    Q_ASSERT(openglProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                   ":/vert-shader.vsh"));

    Q_ASSERT(openglProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                   ":/frag-shader.fsh"));

    Q_ASSERT(openglProgram.link());
    Q_ASSERT(openglProgram.bind());

    perspective.aspectRatio =  height() > 0.0f ? float(width()) / float(height()) : 1.0f;

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE); //myChange 片面のみ表示する設定（コメントアウなしで有効だと回転途中で見えなくなってしまう。） 透明の時もこれで実際OKだった。　//チュートリアルによると有効にするべきかもしれないが、今回はそうしていない。→ (glDesableをオフが必須とのこと）http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-10-transparency/

    glEnable(GL_BLEND); //myChange 透明表示のため追加
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //myChange 透明表示のため追加

}

void QObj3dViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projectionMat.setToIdentity();
    projectionMat.perspective(perspective.verticalAngle, perspective.aspectRatio, perspective.nearPlane, perspective.farPlane);

    viewMat.setToIdentity();
    viewMat.lookAt(lookAt.eye, lookAt.center, lookAt.up);

    modelMat.setToIdentity();
    modelMat.scale(modelScale);
    modelMat.rotate(modelRotation);
    modelMat.translate(modelTranslation);

    openglProgram.enableAttributeArray("vertexPosition");
    openglProgram.setAttributeArray("vertexPosition", triangles.constData());

    openglProgram.enableAttributeArray("vertexNormal");
    openglProgram.setAttributeArray("vertexNormal", normals.constData());

    openglProgram.enableAttributeArray("vertexUV_a");
    openglProgram.setAttributeArray("vertexUV_a", textureUV.constData());

    if(texture != Q_NULLPTR)
    {
        openglProgram.setUniformValue("renderTexture", true);
        openglProgram.setUniformValue("texture", 0);
        texture->bind();
    }
    else
    {
        openglProgram.setUniformValue("renderTexture", false);
    }

    openglProgram.setUniformValue("normalMatrix", modelMat.normalMatrix()); // world normal
    openglProgram.setUniformValue("modelViewMatrix", viewMat * modelMat);
    openglProgram.setUniformValue("projectionMatrix", projectionMat);
    openglProgram.setUniformValue("modelViewProjMatrix", projectionMat * viewMat * modelMat);

    openglProgram.setUniformValue("lightPosition", lightPosition);
    openglProgram.setUniformValue("lightKd", lightKd);
    openglProgram.setUniformValue("lightLd", lightLd);

    //-start- myChange [DEBUG] テストデータ1平面　色設定用
    QVector<QVector3D> colors;
    //-start- NG
    //colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
    //       << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
    //       << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
    //       << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0);
    //-end- NG
    for(int i=0; i<triangles.count(); i++){
        if(i < 1) {
            colors.append(QVector3D(1, 0, 0));
            colors.append(QVector3D(1, 0, 0));
            colors.append(QVector3D(1, 0, 0));
        } else {
            colors.append(QVector3D(0, 0, 1));
            colors.append(QVector3D(0, 0, 1));
            colors.append(QVector3D(0, 0, 1));
        }
    }
    openglProgram.setAttributeArray("color", colors.constData());
    openglProgram.enableAttributeArray("color");
    //-end- myChange [DEBUG] 1平面用

    //-start- myChange [DEBUG] テストデータ1平面　半透明色設定用
    QVector<float> acolors;
    for(int i=0; i<triangles.count(); i++){
        if(i < 1) {
            acolors.append(0.3);
        } else {
            acolors.append(1.0);
        }
    }
    openglProgram.setAttributeArray("acolor", colors.constData());
    openglProgram.enableAttributeArray("acolor");
    //-end- myChange [DEBUG] 1平面用　半透明色設定用

    glDrawArrays(GL_TRIANGLES, 0, triangles.count());

    //qDebug() << "[DEBUG]qobj3dviewr.cpp-paintGL";
}

void QObj3dViewer::resizeGL(int w, int h)
{
    perspective.aspectRatio =  h > 0.0f ? float(w) / float(h) : 1.0f;
}

void QObj3dViewer::setRotation(float angle, float x, float y, float z)
{
    modelRotation = QQuaternion::fromAxisAndAngle(x, y, z, angle);
}

void QObj3dViewer::setTranslation(float x, float y, float z)
{
    modelTranslation = QVector3D(x, y, z);
}

void QObj3dViewer::setScale(float s)
{
    modelScale = s;
}

void QObj3dViewer::setPerspective(float verticalAngle, float nearPlane, float farPlane)
{
    perspective.verticalAngle = verticalAngle;
    perspective.nearPlane = nearPlane;
    perspective.farPlane = farPlane;
}

void QObj3dViewer::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    lookAt.eye = eye;
    lookAt.center = center;
    lookAt.up = up;
}

void QObj3dViewer::setLighting(const QVector3D &lightPos, const QVector3D &kd, const QVector3D &ld)
{
    lightPosition = lightPos;
    lightKd = kd;
    lightLd = ld;
}

void QObj3dViewer::setTextureFile(const QString &file)
{
    if(texture == Q_NULLPTR)
        delete texture;
    texture = new QOpenGLTexture(QImage(file).mirrored());
}

void QObj3dViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::DEBUG01_setTriangles(QVector<QOpenGLTriangle3D> &_triangles)
{
    triangles.clear();
    normals.clear();

    for(int i=0; i<_triangles.count(); i++)
    //for(int i=0; i<6; i++)
    {
        triangles.append(_triangles.at(i).p1);
        triangles.append(_triangles.at(i).p2);
        triangles.append(_triangles.at(i).p3);

        normals.append(_triangles.at(i).p1Normal);
        normals.append(_triangles.at(i).p2Normal);
        normals.append(_triangles.at(i).p3Normal);

        textureUV.append(_triangles.at(i).p1UV);
        textureUV.append(_triangles.at(i).p2UV);
        textureUV.append(_triangles.at(i).p3UV);
    }

    update();
}
