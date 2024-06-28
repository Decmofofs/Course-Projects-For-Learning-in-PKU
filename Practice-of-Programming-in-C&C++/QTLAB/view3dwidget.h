#ifndef VIEW3DWIDGET_H
#define VIEW3DWIDGET_H

#include <QObject>
#include <QThread>
#include <string>

class view3dwidget : public QObject
{
    Q_OBJECT

private:

public:

    static view3dwidget* View3DPlayer;

    std::string filename;
    view3dwidget(std::string filename, QObject *parent = nullptr);
    ~view3dwidget();

public slots:
    void work();

signals:
    void ToDo();

};
#endif // VIEW3DWIDGET_H
