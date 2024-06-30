#include "objwriter.h"
#include <QString>
#include <QApplication>
#include <QProcess>
#include "picturewidget.h"
#include "QDebug"
#include "cstdio"
objWriter::objWriter() {}

unsigned objWriter::SMOOTH = 0;
unsigned objWriter::CUBE = 1;

void objWriter::getMesh(const std::string& file) {
    QString s = PictureWidget::filerootApplication->applicationDirPath();
    //if (s != "") s += '/';
    QString root = "";
    std::string root_2 = "";
    int len = s.length();
    for(int i = 0; i < len-6; ++i){
        root += s[i];

    }
    qDebug() << root;
    std::string file_path=(std::string)(root.toLatin1().data())+"/debug/meshes/"+file+"_mesh.mesh";
    qDebug() << file_path;
    std::remove(file_path.c_str());
    QProcess* p = new QProcess();
    QString command = "balsam.exe";
    QStringList arguments;
    arguments << root + "/"+QString(file.c_str()) + ".obj"<<"-o"<<root+"/debug";

    p->start(command, arguments);
    p->waitForStarted();
    p->waitForFinished();
    QObject::connect(p, &QProcess::finished, p, &QObject::deleteLater);
}

void objWriter::SmoothMesh(heightGraph& graph, const Vector2& start_position, const std::string& file) {
    std::ofstream fout(file + ".obj");

    fout << "o " << file << std::endl << std::endl;

    int height = (int)graph.size.x;
    int width = (int)graph.size.y;

    int startx = (int)start_position.x;
    int starty = (int)start_position.y;

    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            fout << "v " << i + startx << ' ' << graph[i][j] << ' ' << j + starty << std::endl;
        }
    }
    fout << std::endl;

    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < width - 1; ++j) {
            fout << 'f';
            fout << ' ' << i * width + j + 1;
            fout << ' ' << i * width + (j + 1) + 1;
            fout << ' ' << (i + 1) * width + j + 1;
            fout << std::endl;

            fout << 'f';
            fout << ' ' << i * width + (j + 1) + 1;
            fout << ' ' << (i + 1) * width + (j + 1) + 1;
            fout << ' ' << (i + 1) * width + j + 1;
            fout << std::endl;
        }
    }

    fout.close();

    getMesh(file);
}

int _h = 0, _w = 0;
unsigned g3tov (unsigned i, unsigned j, unsigned k) {
    return (i * (_w - 1) + j) * 4 + k + 1;
}

void objWriter::CubeMesh(heightGraph& graph, const Vector2& start_position, const std::string& file){
    std::ofstream fout(file + ".obj");

    fout << "o " << file << std::endl << std::endl;

    int height = (int)graph.size.x;
    int width = (int)graph.size.y;
    _h = height; _w = width;

    int startx = (int)start_position.x;
    int starty = (int)start_position.y;

    unsigned flatten = 2;

    // vertices
    for(int i = 0; i < height - 1; ++i){
        for(int j = 0; j < width - 1; ++j){
            fout << "v " << (i + startx) * flatten << ' ' << (int)graph[i][j] << ' ' << (j + starty) * flatten << std::endl;
            fout << "v " << (i + startx) * flatten << ' ' << (int)graph[i][j] << ' ' << (j + starty + 1) * flatten << std::endl;
            fout << "v " << (i + startx + 1) * flatten << ' ' << (int)graph[i][j] << ' ' << (j + starty + 1) * flatten << std::endl;
            fout << "v " << (i + startx + 1) * flatten << ' ' << (int)graph[i][j] << ' ' << (j + starty) * flatten << std::endl;
        }
    }
    fout << std::endl;

    // top faces
    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < width - 1; ++j) {
            int s = i * (width - 1) * 4 + j * 4 + 1;
            fout << 'f';
            for (int k = 0; k < 4; ++k) {
                fout << ' ' << s + k;
            }
            fout << std::endl;
        }
    }
    fout << std::endl;

    // side faces
    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < width - 2; ++j) {
            if ((int)graph[i][j] != (int)graph[i][j + 1]) {
                fout << "f " << g3tov(i,j,2) << ' ' << g3tov(i,j,1) << ' ' << g3tov(i,j+1,0) << ' ' << g3tov(i,j+1,3) << std::endl;
            }
        }
    }
    for (int i = 0; i < height - 2; ++i) {
        for (int j = 0; j < width - 1; ++j) {
            if ((int)graph[i][j] != (int)graph[i + 1][j]) {
                fout << "f " << g3tov(i,j,3) << ' ' << g3tov(i,j,2) << ' ' << g3tov(i+1,j,1) << ' ' << g3tov(i+1,j,0) << std::endl;
            }
        }
    }


    fout.close();

    getMesh(file);
}

void objWriter::Edge(heightGraph& graph, unsigned shape, const Vector2& start_position, const std::string& file){
    std::ofstream fout(file + ".obj");

    int t = shape * int(start_position.x);
    if (t > 0) return;

    fout << "o " << file << std::endl << std::endl;

    int height = (int)graph.size.x;
    int width = (int)graph.size.y;

    for(int i = 0; i < height - 1; ++i) {
        fout << "v " << i << " 0 0" << std::endl;
        fout << "v " << i << ' ' << graph[i][0] << " 0" << std::endl;
    }

    for(int j = 0; j < width - 1; ++j){
        fout << "v " << height - 1 << " 0 " << j << std::endl;
        fout << "v " << height - 1 << ' ' << graph[height - 1][j] << ' ' << j << std::endl;
    }

    for(int i = height - 1; i > 0; --i) {
        fout << "v " << i << " 0 " << width - 1 << std::endl;
        fout << "v " << i << ' ' << graph[i][width - 1] << ' ' << width - 1 << std::endl;
    }

    for(int j = width - 1; j > 0; --j){
        fout << "v 0 0 " << j << std::endl;
        fout << "v 0 " << graph[0][j] << ' ' << j << std::endl;
    }

    fout << std::endl;

    for (int i = 0; i < 2 * (height + width - 2) - 1; ++i){
        fout << "f " << 1;
    }

    getMesh(file);
}
