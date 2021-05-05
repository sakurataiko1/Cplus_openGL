#include "miwidget.h"
#include <QMouseEvent>
#include <QMouseEventTransition>
#include <qmouseeventtransition.h>
#include <QSurfaceFormat>
//#include <mainwindow.h>
//#include <ui_mainwindow.h>
#include <GL/GLU.h>
#include <gl/GL.h>

#include <QScopedPointer>

//for Drag&Drop
#include <QMimeData>

//ProgressBar
#include <QProgressBar>
#include <QProgressDialog>

//for Japanese
#include <QTextCodec>

#define NA(i,j,k) (i)*ny*nz+(j)*nz+(k)

miWidget::miWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
     paintExeFlag = 0;
}

miWidget::~miWidget(){
//     m_program->disableAttributeArray(m_vertexLocation);
//     m_program->disableAttributeArray(m_colorLocation);
//     m_program->disableAttributeArray(m_normalLocation);
//     m_program->release();

}

//void miWidget::clearFrame()
//{
//     initializeGL();
//}

//void miWidget::initializeGL()
//{
//     //初期化(OpenGL APIコール前に必要)
//     initializeOpenGLFunctions();

//     //shader------------------------------
//     m_program.reset(new QOpenGLShaderProgram(this));
//     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
//              "attribute vec3 position;\n"
//              "attribute vec3 sourceColor;\n"
//              "attribute vec3 normal;\n"
//              "uniform mat4 mvpMatrix;\n"
//              "uniform mat4 invMatrix;\n"
//              "uniform vec3 lightDirection;\n"

//              "uniform mat4 modelViewerpMatrix;\n"
//              "uniform mat4 projectionMatrix;\n"
//              "varying vec4 color;\n"
//              "varying vec4 vColor;\n"

//              "void main()\n"
//              "{\n"
//              "  color = vec4(sourceColor, 1.0);\n"
//              "  vec3 invLight = normalize(invmatrix *vec4(lightDirection, 0.0)).xyz;\n"
//              "  float diffuse = clamp(dot(normal, invLight), 0.1, 1.0);\n"
//              "}");


//      m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
//               "varying vec4 vColor;\n"
//               "void main()\n"
//               "{\n"
//               "gl_FragColor = vColor;\n"
//               "}");

//      m_program->link();
//      m_program->bind();

//      //attribute
//      m_vertexLocation = m_program->attributeLocation("position");
//      m_colorLocation = m_program->attributeLocation("sourceColor");
//      m_normalLocation = m_program->attributeLocation("normal");

//      //uniform
//      m_mvpmatrixLocation = m_program->uniformLocation("mvpMatrix");
//      m_mvpmatrixLocation = m_program->uniformLocation("invMatrix");
//      m_mvpmatrixLocation = m_program->uniformLocation("lightDirection");

//}


//void miWidget::resizeGL(int w, int h)
//{
//     //ビューポート変換　左下隅の座標(x), (y), ウィンドウ幅(W), 高さ(H)
//    glViewport(0, 0, w, h);
//    widgetSizeX = GLfloat(w);
//    widgetSizeX = GLfloat(h);

//    aspectRatio = qreal(w)/qreal(h ? h : 1);

//}


//void miWidget::paintGL()
//{
//    QVector<GLfloat> lightDirection = {-0.5f, 0.5f, 0.5f};

//    if(paintExeFlag == 1){
//        //座標読み込み
//        grafficSurface();

//        rotate_x = 0.0f;
//        rotate_y = 0.0f;

//        mMatrix = QMatrix4x4(); //必ずリセット
//        mMatrix.translate(QVector3D(0.0, 0.0, -0.5));
//        mMatrix.rotate(rotate_x,rotate_y,rotate_z,0.0f);

//        vMatrix = QMatrix4x4();
//        vMatrix.lookAt(QVector3D(0.0, 0.0, 2.0), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

//        pMatrix = QMatrix4x4();
//        pMatrix.setToIdentity();
//        pMatrix.perspective(45, aspectRatio, 0.1f, 100.0f);

//        mvpMatrix = pMatrix * vMatrix * mMatrix;

//        invMatrix = mvpMatrix.inverted();

//        //読み込んだ座標からシェーダー、バッファオブジェクトを生成(exeFlat = 1 で実行し、処理終了後 exeFlag = 2 で返す)

//        //Shader Programに渡す値を渡す領域の定義
//        m_program->enableAttributeArray(m_vertexLocation);
//        m_program->enableAttributeArray(m_colorLocation);
//        m_program->enableAttributeArray(m_normalLocation);


//        //Shader Programに頂点配列をセットする
//        m_program->setAttributeArray(m_vertexLocation, vertexList.constData(), 3, 0);
//        m_program->setAttributeArray(m_colorLocation, vertexList.constData(), 3, 0);
//        m_program->setAttributeArray(m_normalLocation, vertexList.constData(), 3, 0);

//        m_program->setUniformValue(m_mvpmatrixLocation, mvpMatrix);
//        m_program->setUniformValue(m_invmatrixLocation, invMatrix);
//        m_program->setUniformValue(m_lightDirectionLocation, lightDirection.at(0), lightDirection.at(1), lightDirection.at(2));

//        m_program->bind();
//        m_program->release();

//        paintExeFlag=2;
//    }
//    //-end- if(paintExeFlag == 1)

//    if(paintExeFlag == 2){
//        paintExeFlag = 3;
//    }

//    if(paintExeFlag == 3){
//        mMatrix = QMatrix4x4();
//        mMatrix.rotate(-rotate_x, -rotate_x, -rotate_z, 0.0f);

//        mvpMatrix = QMatrix4x4();
//        mvpMatrix = pMatrix * vMatrix * mMatrix;


//        //Shader Programに渡す値を渡す領域の定義
//        m_program->setUniformValue(m_mvpmatrixLocation, mvpMatrix);
//        m_program->bind();

//        glDrawArrays(GL_QUADS,0, vertexList.size()/4);
//        glFlush();
//    }
//    //-end- if(paintExeFlag == 3)
//}

//void miWidget::dragEnterEvent(QDragEnterEvent *e)
//{
//    if(e->mimeData()->hasUrls()){
//        e->acceptProposedAction();
//    }
//}

//void miWidget::dropEvent(QDropEvent *e)
//{
//     dragFilePathList.clear();
//     if(e->mimeData()->hasUrls()){
//         foreach (QUrl url, e->mimeData()->urls()){
//             dragFilePathList << url.toLocalFile();
//             qDebug() << url.toLocalFile();
//         }
//     }

//     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//     mMatrix = QMatrix4x4();
//     mMatrix.setToIdentity();

//     DrawMesh.clear();
//     DrawSurface.clear();
//     mateNoList.clear();
//     mateNoOfMesh.clear();

//     vertexList.clear();
//     colorList.clear();
//     normalList.clear();

//     m_program->disableAttributeArray(m_vertexLocation);
//     m_program->disableAttributeArray(m_colorLocation);
//     m_program->disableAttributeArray(m_normalLocation);

//     m_program->release();

//     //各メッシュの材質No. を取得
//     getMateNumOfMesh();

//     //描画するメッシュの面情報を取得
//     checkMateNumAdjoinMesh();

//     //paintGL実行フラグ有効
//     paintExeFlag = 1;

//}

//本文277行目
void miWidget::grafficSurface()
{
//    //多分　参考にしている？ http://www.natural-science.or.jp/article/20091110211125.php
//    //----------------------------------------------------
//    // 物質質感の定義
//    //----------------------------------------------------
//    struct MaterialStruct {
//      GLfloat ambient[4];
//      GLfloat diffuse[4];
//      GLfloat specular[4];
//      GLfloat shininess;
//    };
//    //jade(翡翠)
//    MaterialStruct ms_jade = {
//      {0.135,     0.2225,   0.1575,   1.0},
//      {0.54,      0.89,     0.63,     1.0},
//      {0.316228,  0.316228, 0.316228, 1.0},
//      12.8};
//    //ruby(ルビー)
//    MaterialStruct ms_ruby  = {
//      {0.1745,   0.01175,  0.01175,   1.0},
//      {0.61424,  0.04136,  0.04136,   1.0},
//      {0.727811, 0.626959, 0.626959,  1.0},
//      76.8};

//    //陰影ON-----------------------------
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);//光源0を利用
//    glEnable(GL_CULL_FACE);
//    glDepthFunc(GL_LEQUAL);
//    //-----------------------------------

//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ms_jade.ambient);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ms_jade.diffuse);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms_jade.specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &ms_jade.shininess);

//    drawSurfaceOfMesh(0);

//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ms_ruby.ambient);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ms_ruby.diffuse);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms_ruby.specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &ms_ruby.shininess);

//    drawSurfaceOfMesh(37);

    for(int i=0; i<mateNoList.size(); i++){
        drawSurfaceOfMesh(mateNoList.at(i));
    }
}

void miWidget::grafficLines()
{
    glBegin(GL_LINES); // glEnd() と対になる

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(20, 0, 0);

    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 20, 0);

    glColor3f(0, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);

    glEnd(); //glBegin() と対になる
}

void miWidget::drawSurfaceOfMesh(int mateNo) {
    QList<unsigned int> drawMeshList = DrawMesh.values(mateNo);
    int i,j,k;
    i=0;
    j=0;
    k=0;

    for(int m=0; m < drawMeshList.size(); m++){
        //QList<int> drawSurfaceList = DrawSurface.values(drawMeshList.at(m));
        QList<unsigned int> drawSurfaceList = DrawSurface.values(drawMeshList.at(m)); //[DEBUG]kuroda 型合わせしないとエラーになるので変換したが、unsignedだとマイナス取れないのでこれでいいのか？？

        //qDebug() << "[DEBUG]miWidget.cpp - drawSurfaceOfMesh m=" << QString::number(m) << "drawMeshList.at(m)= " << drawMeshList.at(m);
        QList<int> meshXYZ = getXYZ(drawMeshList.at(m));
        i = meshXYZ.at(0);
        j = meshXYZ.at(1);
        k = meshXYZ.at(2);

        //座標定義
        for(int n=0; n< drawSurfaceList.size(); n++){
            getPointOfMesh(i, j, k, drawSurfaceList.at(n), mateNo);
        }
    }
}

//voxファイルを読み込んで、メッシュごとにマテリアルNo.を割り当てる
void miWidget::getMateNumOfMesh()
{
     //voxfilePath = dragFilePathList.at(0);
     QStringList read_vox = readTextFileAll(voxfilePath);
     qDebug() << "read_vox.size" << read_vox.size();

     int voxflag = 0;

     //初期値
     meshsize = 1.0;

     //進捗表示のバー
//     QProgressDialog pd(this);
//     pd.setRange(0, read_vox.size());
//     pd.setWindowModality(Qt::WindowModal);
//     pd.setLabelText(TR("Getting Material No. of Mesh"));
//     qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
//     if(pd.wasCanceled()){
//         exit(false);
//     }

     for(int line_n=0; line_n < read_vox.size(); line_n++){ //-2;
//       pd.setValue(line_n);
         if(read_vox.at(line_n).trimmed() == "" ){ continue; }; //kuroda

         //qDebug() << "miWidget::getMateNumOfMesh() read_vox.at(line_n).trimmed()=" << read_vox.at(line_n).trimmed();

         if(read_vox.at(line_n).trimmed()=="CellData"){
             voxflag = 2;
             line_n = line_n + 1;
             //qDebug() << "miWidget::getMateNumOfMesh() CellData voxflag=" << QString::number(voxflag);
         }

         QStringList temp01 = read_vox.at(line_n).split("\t");

         if(voxflag != 2 && temp01.size()>1){ //これがないとプログラムがクラッシュして、立体画面が起動しない
             //メッシュサイズ
             if(temp01.at(1) == "unitlength"){
                 meshsize = temp01.at(0).toFloat();
                 voxflag = 1;
                 //line_n = line_n+1;
             }
             //マテリアルNo & 名前
             if(voxflag == 1){
                 QStringList temp02 = read_vox.at(line_n).split("\t");
                 mateNoList << temp02.at(0).toInt();
                 mateNameList << temp02.at(1);
                 //line_n = line_n + 1;
             }
         }

         if(voxflag == 2){
             nx = (int)read_vox.at(line_n).split(" ").at(0).toInt();
             ny = (int)read_vox.at(line_n).split(" ").at(2).toInt();
             nz = (int)read_vox.at(line_n).split(" ").at(4).toInt();
             voxflag = 3;
             line_n = line_n+1;
         }

         if(voxflag == 3 ){
             QStringList temp03 = read_vox.at(line_n).split(" ");
             //qDebug() << "miWidget::getMateNumOfMesh() temp03=" << temp03;
             //materialNoの個数を抽出->cnt
             for(int i=0; i<temp03.size()/2; i++){
                 int cnt = temp03.at(2*i + 1).toInt();

                 for(int j=0; j<cnt; j++){
                     mateNoOfMesh << temp03.at(2*i).toInt();
                 }
             }
         }
     }
     //-end- for(int line_n=0; line_n < read_vox.size(); line_n++)

     //プログレスバーのMAXを100にするため
//     pd.setValue(read_vox.size());

     //正規化
     int maxn;

     //xyzメッシュ数最大値取得
     maxn = nx;
     if(ny > maxn){maxn = ny;}
     if(nz > maxn){maxn = nz;}

     meshsize_x = meshsize;
     meshsize_y = meshsize;
     meshsize_z = meshsize;

}

void miWidget::checkMateNumAdjoinMesh()
{
    int i,j,k;
    meshAll = nx*ny*nz;
    unsigned int nowMeshNo = 0;
    unsigned int chkMeshNo = 0;
    int drawMeshFlag;

    //QProgressDialog pd(this);
    //pd.setRange(0, meshAll/1000);
    //pd.setWindowModality(Qt::WindowModal);
    //pd.setLabelText(TR("Selecting Drawing Mesh"));
    //qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    //if(pd.wasCanceled()){
    //    exit(false);
    //}

    for(k=0; k<nz; k++){
        for(j=0; j<ny; j++){ //kuroda nz→nyに修正
            for(i=0; i<nx; i++){
                drawMeshFlag = 0;
                if(k==0 && j==0&& i==0){
                    nowMeshNo = 0;
                }else {
                    nowMeshNo++; //kuroda 追加。この記述をいれたので iループの最後の nowMeshNo記述をコメントアウトした。
                }

                //qDebug()  << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() k=" << k << " j=" << j << " i=" <<i << "nowMeshNo=" << QString::number(nowMeshNo);
                //qDebug()  << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() DrawMesh=" << DrawMesh;

                int drawSurface_flag = 0;
                //front
                drawSurface_flag = 0;
                chkMeshNo = nowMeshNo - nx * ny;
                //qDebug() << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() front chkMeshNo=" << QString::number(chkMeshNo) ;
                if(j == 0){ //front ～ backそれぞれ、この1行違いあり //変更前→k==0
                    drawSurface_flag = 1;
                } else {
                     if(chkMeshNo >= 0 && chkMeshNo < mateNoOfMesh.size()){
                        if(mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]){ drawSurface_flag = 1; }
                    }
                }
                //if(k==0 || ((k !=0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]))){ if(drawSurface_flag == 1){
                if(drawSurface_flag == 1){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                    }
                    DrawSurface.insert(nowMeshNo,1); //front ～ backそれぞれ、この1行違いあり
                }

                //back
                drawSurface_flag = 0;
                chkMeshNo = nowMeshNo + nx * ny;
                //qDebug() << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() back chkMeshNo=" << QString::number(chkMeshNo) ;
                if(j == ny-1){ //front ～ backそれぞれ、この1行違いあり //変更前 k==nz-1
                    drawSurface_flag = 1;
                } else {
                    if(chkMeshNo >= 0 && chkMeshNo < mateNoOfMesh.size()){
                        if(mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]){ drawSurface_flag = 1; }
                    }
                }
                //if(k== nz-1 || ((k != nz-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]))){
                if(drawSurface_flag == 1){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                    }
                    DrawSurface.insert(nowMeshNo,2); //front ～ backそれぞれ、この1行違いあり
                }

                //right
                drawSurface_flag = 0;
                chkMeshNo = nowMeshNo + 1;
                //qDebug() << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() right chkMeshNo=" << QString::number(chkMeshNo) ;
                if(i == nx-1){ // front ～ backそれぞれ、この1行違いあり
                    drawSurface_flag = 1;
                } else {
                    if(chkMeshNo >= 0 && chkMeshNo < mateNoOfMesh.size()){
                        if(mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]){ drawSurface_flag = 1; }
                    }
                }
                //if(i== nx-1 || ((i != nx-1 ) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]))){
                if(drawSurface_flag == 1){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                    }
                    DrawSurface.insert(nowMeshNo,3); //front ～ backそれぞれ、この1行違いあり
                }

                //left
                drawSurface_flag = 0;
                chkMeshNo = nowMeshNo - 1;
                //qDebug() << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() left chkMeshNo=" << QString::number(chkMeshNo) ;
                if(k == 0){ // front ～ backそれぞれ、この1行違いあり //変更前 i==0
                    drawSurface_flag = 1;
                } else {
                    if(chkMeshNo >= 0 && chkMeshNo < mateNoOfMesh.size()){
                        if(mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]){ drawSurface_flag = 1; }
                    }
                }
                //if(i== 0 || ((i != 0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]))){
                if(drawSurface_flag == 1){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                    }
                    DrawSurface.insert(nowMeshNo,4); //front ～ backそれぞれ、この1行違いあり
                }

                //top
                drawSurface_flag = 0;
                chkMeshNo = nowMeshNo + nx * ny; //変更前→chkMeshNo = nowMeshNo - nx;
                //qDebug() << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() top chkMeshNo=" << QString::number(chkMeshNo) ;
                if(k == nz-1){ // front ～ backそれぞれ、この1行違いあり //変更前: j==ny-1
                    drawSurface_flag = 1;
                } else {
                    //(j != ny-1)の場合
                    if(chkMeshNo >= 0 && chkMeshNo < mateNoOfMesh.size()){
                        if(mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]){ drawSurface_flag = 1; }
                    }
                }
                //if(j==ny-1 || ((j != ny-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]))){
                if(drawSurface_flag == 1){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                    }
                    DrawSurface.insert(nowMeshNo,5); //front ～ backそれぞれ、この1行違いあり
                }

                //bottom
                chkMeshNo = nowMeshNo - nx * ny; //変更前　nowMeshNo - nx;
                //qDebug() << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh() bottom chkMeshNo=" << QString::number(chkMeshNo) ;
                if(k == 0){ // front ～ backそれぞれ、この1行違いあり //変更前 j==0
                    drawSurface_flag = 1;
                } else {
                    //(j != 0)の場合
                    if(chkMeshNo >= 0 && chkMeshNo < mateNoOfMesh.size()){
                        if(mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]){ drawSurface_flag = 1; }
                    }
                }
                //if(j==0 || ((j != 0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo]))){
                if(drawSurface_flag == 1){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                    }
                    DrawSurface.insert(nowMeshNo,6); //front ～ backそれぞれ、この1行違いあり
                }

                //kuroda commentout//　nowMeshNo++;

            }//-end- for i
         }//-end- for j
    }//-end- for(k=0; k<nz; k++)

    //qDebug() << "[DEBUG]miWidget.cpp-checkMateNumAdjoinMesh()nx=" << QString::number(nx) << " ny=" << QString::number(ny) << QString::number(nx) << " nz=" << QString::number(nz);

}

QList<int> miWidget::getXYZ(unsigned int meshNo) //1次元リストとしてのインデックス番号の取得？
{
     int i,j,k;
     QList<int> XYZ;

     int nxny = nx * ny;

     int tempxy;
     k = meshNo / nxny;

     tempxy = meshNo % nx;

     j=tempxy / nx;
     i=tempxy % nx;

     XYZ << i;
     XYZ << j;
     XYZ << k;

     return XYZ;
}


void miWidget::getPointOfMesh(int i, int j, int k, int surfaceNo, int input_MateNo)
{
     QString vertexP;
     QStringList vertexName ;

     myfunction *m_myfunction = new myfunction;
     QVector3D tmpColorVector = m_myfunction->func_defineColor(input_MateNo);

     //1:front 2:back 3:right 4:left 5:top 6:bottom

     //front
     if(surfaceNo == 1){
         vertexName << "A" << "B" << "C" << "D" ;
         //glNormal3f(0.0, 0.0, -1.0)
         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << 0.0;
             normalList << 1.0;
         }
     }

     //back
     if(surfaceNo == 2){
         vertexName << "E" << "F" << "G" << "H" ;

         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << 0.0;
             normalList << -1.0;
         }
     }

     //right
     if(surfaceNo == 3){
         vertexName << "B" << "F" << "G" << "C" ;

         for(int n=0; n<4; n++){
             normalList << 1.0;
             normalList << 0.0;
             normalList << 0.0;
         }
     }

     //left
     if(surfaceNo == 4){
         vertexName << "E" << "A" << "D" << "H" ;

         for(int n=0; n<4; n++){
             normalList << -1.0;
             normalList << 0.0;
             normalList << 0.0;
         }
     }

     //top
     if(surfaceNo == 5){
         vertexName << "D" << "C" << "G" << "H" ;

         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << 1.0;
             normalList << 0.0;
         }
     }

     //bottom
     if(surfaceNo == 6){
         vertexName << "E" << "F" << "B" << "A" ;

         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << -1.0;
             normalList << 0.0;
         }
     }

     //指定された面を描画
     GLfloat nowOP_x, nowOP_y , nowOP_z;
     GLfloat x,y,z;
     for(int n=0; n<vertexName.size(); n++){
         //もと:松岡さんより流用//nowOP_x = i*meshsize_x -0.5;
         //もと:松岡さんより流用//nowOP_y = i*meshsize_y -0.5;
         //もと:松岡さんより流用//nowOP_z = i*meshsize_z -0.5;

         nowOP_x = i*meshsize_x; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
         nowOP_y = j*meshsize_y; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
         nowOP_z = k*meshsize_z; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処

         vertexP = vertexName.at(n);

         //Aを(0, 0, 0) に設定した場合
         if(vertexP == "A"){ //頂点A(0,0,0)
             x = nowOP_x;
             y = nowOP_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "B"){ //頂点B(1,0,0)
             x = nowOP_x + meshsize_x;
             y = nowOP_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "C"){ //頂点B(1,1,0)
             x = nowOP_x + meshsize_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "D"){ //頂点D(0,1,0)
             x = nowOP_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "E"){ //頂点D(0,0,1)
             x = nowOP_x;
             y = nowOP_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "F"){ //頂点D(1,0,1)
             x = nowOP_x;
             y = nowOP_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "G"){ //頂点D(0,0,1)
             x = nowOP_x + meshsize_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "H"){ //頂点D(0,0,1)
             x = nowOP_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }
     }//-end- for(int n=0; n<vertexName.size(); n++)
}

//ファイル書き込み(windowsで使うファイル用)
void miWidget::fileWrteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList)
{
     QFile file(WriteFilePath);
     if(WriteMode == "Append"){
         if(!file.open(QIODevice::Append| QIODevice::Text)){
             QMessageBox::information(this, tr("Unable to openfile"), file.errorString());
             return;
         }
     } else {
         if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
             QMessageBox::information(this, tr("Unable to openfile"), file.errorString());
             return;
         }
     }

     QTextStream out(&file);
     for (int n=0; n<msgList.size(); n++){
         out << msgList.at(n) << endl;
     }
     file.close();
}

QStringList miWidget::readTextFileAll(QString fileName)
{
    QStringList lines;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QString errStr =  "file open error:" + file.errorString();
        qDebug() << errStr;
        return(lines);
    }
    QTextStream in(&file);
    QString inStr = in.readAll();
    file.close();

    //voxファイルのLF改行に対応
    //QStringList lines = inStr.split("\r\n");
    lines = inStr.split("\r\n");
    lines = inStr.split("\n");
    return lines;

}

void miWidget::readTextFileLine(QString fileName)
{
     QFile file(fileName);
     if(!file.open(QIODevice::ReadOnly)){
         QString errStr =  "file open error:" + file.errorString();
         qDebug() << errStr;
         return;
     }
     QTextStream in(&file);
     while(! in.atEnd()){
         qDebug() << in.readLine();
     }
     file.close();
}

//QVector<GLfloat> miWidget::func_get_voxGraffic(QString in_voxfilepath, QString mode){  //[DEBU]kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
QVector<QVector3D>  miWidget::func_get_voxGraffic(QString in_voxfilepath, QString mode){  //[DEBU]kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
    dragFilePathList.clear();
    dragFilePathList << in_voxfilepath;
    voxfilePath = in_voxfilepath;

    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    mMatrix = QMatrix4x4();
    mMatrix.setToIdentity();

    DrawMesh.clear();
    DrawSurface.clear();
    mateNoList.clear();
    mateNoOfMesh.clear();

    vertexList.clear();
    colorList.clear();
    normalList.clear();

    g_verticesVector.clear();
    g_colorsVector.clear();

    //m_program->disableAttributeArray(m_vertexLocation);
    //m_program->disableAttributeArray(m_colorLocation);
    //m_program->disableAttributeArray(m_normalLocation);
    //
    //m_program->release();

    //各メッシュの材質No. を取得
    getMateNumOfMesh();
    QList<int> tmpQList;
    for(int i=0; i<mateNoOfMesh.size(); i++ ){ tmpQList << mateNoOfMesh[i]; } //[DEBUG]kuroda qDebug表示のため、QListに代入する。
    qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic  mateNoOfMesh size=" << QString::number(mateNoOfMesh.size()) << ""  << tmpQList;

    //描画するメッシュの面情報を取得
    checkMateNumAdjoinMesh();
    qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawMesh=" << DrawMesh;
    qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawSurface=" << DrawSurface;

    //paintGL実行フラグ有効
    paintExeFlag = 1;

    grafficSurface(); //voxから shaderで描くための図形取得　vertexList, colorList (normalListも？？）

    qDebug() << "[DEBUG]02func_get_voxGraffic.cpp g_verticesVector=" << g_verticesVector;
    //qDebug() << "[DEBUG]02func_get_voxGraffic.cpp g_colorsVector=" << cg_colorsVector;

    if(mode == "color"){
        return g_colorsVector; //QVector<GLfloat> colorList;
    } else {
        return g_verticesVector;   //QVector<GLfloat> vertexList;
    }

}

void miWidget::func_getPointOfMesh_new(int in_i, int in_j, int in_k, int surfaceNo, int input_MateNo) //kuroda　もとのgetPointOfMesh 関数から変更
{
    QString vertexP;
    QStringList vertexName ;

    myfunction *m_myfunction = new myfunction;
    QVector3D tmpColorVector = m_myfunction->func_defineColor(input_MateNo);

    //1:front 2:back 3:right 4:left 5:top 6:bottom

   //頂点の定義
   //   通常座標　と openGLでは違う。　openGLの座標で定義する
   //   通常座標　　　　　FRONT-XY軸:　A=左下　B：右下 C:右上　D:左上　　　　　　　　　　　　　　　　 / BACK-XY軸:　A=左下　B：右下 C:右上　D:左上
   //   通常座標　　　　　FRONT-XY軸: A(0, 0, 0) B(0, 1, 0) C(0, 1, 1) D(0, 0, 1) / BACK-XY軸: A(0, 0, 1) B(0, 1, 1) C(0, 1, 1) D(0, 1, 0)
   //   openGL座標標　FRONT-XY軸: A(0, 0, 0) B(0, 1, 0) C(0, 1, 1) D(0, 0, 1) / BACK-XY軸: A(0, 0, 1) B(0, 1, 1) C(0, 1, 1) D(0, 1, 0)
   //      ※ ①openGL座標では (通常X, 通常-Z, 通常Y) 2番目は上下方向。　3番目は奥行きで。順番が通常と逆。
   //      ※　②openGL座標では　3番目の通常Yは奥行きで手前が＋で後ろがーなので通常座標と+-が逆

    GLfloat nowOP_x, nowOP_y , nowOP_z;
    //GLfloat x,y,z;
    for(int n=0; n<vertexName.size(); n++){
        //もと:松岡さんより流用//nowOP_x = i*meshsize_x -0.5;
        //もと:松岡さんより流用//nowOP_y = i*meshsize_y -0.5;
        //もと:松岡さんより流用//nowOP_z = i*meshsize_z -0.5;

        nowOP_x = in_i * meshsize_x; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
        nowOP_y = in_j * meshsize_y; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
        nowOP_z = in_k * meshsize_z; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処

        // 1メッシュ立方体の頂点座標を定義する。
        QVector3D vertexA = QVector3D(nowOP_x, nowOP_y, nowOP_z);
        QVector3D vertexB = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z);
        QVector3D vertexC = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z);
        QVector3D vertexD = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z);
        QVector3D vertexE = QVector3D(nowOP_x, nowOP_y, nowOP_z-1);
        QVector3D vertexF = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z-1);
        QVector3D vertexG = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z-1);
        QVector3D vertexH = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z-1);

        //1つの正方形平面を作る。　(openGLはすべての図形を 三角形で描くため、２つの三角形で1つの正方形平面を作る。)
        if(surfaceNo == 1){ //Front
            g_verticesVector << vertexA; //１つ目の三角形
            g_verticesVector << vertexB;
            g_verticesVector << vertexC;
            g_verticesVector << vertexC; //2つ目の三角形
            g_verticesVector << vertexD;
            g_verticesVector << vertexA;

            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        if(surfaceNo == 2){ //Back
            g_verticesVector << vertexE; //１つ目の三角形
            g_verticesVector << vertexF;
            g_verticesVector << vertexG;
            g_verticesVector << vertexG; //2つ目の三角形
            g_verticesVector << vertexH;
            g_verticesVector << vertexE;

            g_colorsVector << tmpColorVector;
        }

        if(surfaceNo == 3){ //Right
            g_verticesVector << vertexB; //１つ目の三角形
            g_verticesVector << vertexF;
            g_verticesVector << vertexG;
            g_verticesVector << vertexG; //2つ目の三角形
            g_verticesVector << vertexC;
            g_verticesVector << vertexB;

            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        if(surfaceNo == 4){ //Left
            g_verticesVector << vertexA; //１つ目の三角形
            g_verticesVector << vertexE;
            g_verticesVector << vertexH;
            g_verticesVector << vertexH; //2つ目の三角形
            g_verticesVector << vertexD;
            g_verticesVector << vertexA;

            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        if(surfaceNo == 5){ //Top
            g_verticesVector << vertexD; //１つ目の三角形
            g_verticesVector << vertexC;
            g_verticesVector << vertexG;
            g_verticesVector << vertexG; //2つ目の三角形
            g_verticesVector << vertexH;
            g_verticesVector << vertexD;

            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        if(surfaceNo == 6){ //Bottom
            g_verticesVector << vertexA; //１つ目の三角形
            g_verticesVector << vertexD;
            g_verticesVector << vertexF;
            g_verticesVector << vertexF; //2つ目の三角形
            g_verticesVector << vertexE;
            g_verticesVector << vertexA;

            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

    }
}
