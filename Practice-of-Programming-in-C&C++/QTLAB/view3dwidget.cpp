#include "view3dwidget.h"
#include "picturewidget.h"
#include <QString>
#include <QApplication>

view3dwidget::view3dwidget(std::string filename, QObject *parent)
    : QObject{parent}, filename(filename) {

    QObject::connect(this, &view3dwidget::ToDo, this, &view3dwidget::work);
}

view3dwidget::~view3dwidget() {

}

void view3dwidget::work() {
    QString DirPath = PictureWidget::filerootApplication->applicationDirPath();

    if (PictureWidget::engine) delete PictureWidget::engine;
    PictureWidget::engine = new QQmlApplicationEngine();

    QString file(filename.c_str());
    file += "_mesh.mesh";

    QList<QQmlContext::PropertyPair> QL;
    QQmlContext::PropertyPair p[2] = {{"appDir", DirPath}, {"meshSourceCentre", file}};
    for (int i = 0; i < 2; ++i) {
        QL << p[i];
    }
    PictureWidget::engine->rootContext()->setContextProperties(QL);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        PictureWidget::engine,
        &QQmlApplicationEngine::objectCreationFailed,
        PictureWidget::filerootApplication,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    PictureWidget::engine->load(url);
}

view3dwidget* view3dwidget::View3DPlayer = NULL;
