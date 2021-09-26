#include "qobj3dreader.h"

QObj3dReader::QObj3dReader(QObject *parent) : QObject(parent)
{

}

void QObj3dReader::parseObjFile(const QString &fileName,
                                QStringList &comments,
                                QVector<QOpenGLTriangle3D> &triangles)
{
    comments.clear();
    triangles.clear();

    QFile file(fileName);
    if(file.exists())
    {
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            QVector<QVector3D> v, vn;
            QVector<QVector2D> vt;

            while(!file.atEnd())
            {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0)
                {

                    // if it's a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        comments.append(line.remove(0, 1).trimmed());
                    }

                    // if it's a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        v.append(QVector3D(lineParts.at(1).toFloat(),
                                           lineParts.at(2).toFloat(),
                                           lineParts.at(3).toFloat()));
                    }

                    // if it's a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {
                        vn.append(QVector3D(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat(),
                                            lineParts.at(3).toFloat()));
                    }

                    // if it's a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {
                        vt.append(QVector2D(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat()));
                    }

                    // if it's face data (f)
                    // there's an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        QOpenGLTriangle3D triangle;

                        // get points from v array
                        triangle.p1 = v.at(lineParts.at(1).split("/").at(0).toInt() - 1);
                        triangle.p2 = v.at(lineParts.at(2).split("/").at(0).toInt() - 1);
                        triangle.p3 = v.at(lineParts.at(3).split("/").at(0).toInt() - 1);

                        if(vt.count() > 0) // check if really there are any UV coords
                        {
                            triangle.p1UV = vt.at(lineParts.at(1).split("/").at(1).toInt() - 1);
                            triangle.p2UV = vt.at(lineParts.at(2).split("/").at(1).toInt() - 1);
                            triangle.p3UV = vt.at(lineParts.at(3).split("/").at(1).toInt() - 1);
                        }

                        // get normals from vn array
                        triangle.p1Normal = vn.at(lineParts.at(1).split("/").at(2).toInt() - 1);
                        triangle.p2Normal = vn.at(lineParts.at(2).split("/").at(2).toInt() - 1);
                        triangle.p3Normal = vn.at(lineParts.at(3).split("/").at(2).toInt() - 1);

                        triangles.append(triangle);
                    }

                }
            }

            file.close();
        }
    }
}
