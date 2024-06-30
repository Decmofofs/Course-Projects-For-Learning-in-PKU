#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();

private slots:
    void on_SetMesh_clicked();

    void on_SetPrinter_clicked();

private:
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
