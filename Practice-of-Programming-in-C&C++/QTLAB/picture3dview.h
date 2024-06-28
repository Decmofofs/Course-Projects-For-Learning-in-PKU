#ifndef PICTURE3DVIEW_H
#define PICTURE3DVIEW_H

#include <QQuickWidget>

namespace Ui {
class Picture3DView;
}

class Picture3DView : public QWidget
{
    Q_OBJECT

public:
    explicit Picture3DView(QWidget* n3dWidget, QWidget *parent = nullptr);
    ~Picture3DView();

private:
    Ui::Picture3DView *ui;

};

#endif // PICTURE3DVIEW_H
