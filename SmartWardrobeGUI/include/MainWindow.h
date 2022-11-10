#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>

#include "QCameraWidget.h"
#include "QWardrobeWidget.h"
#include "QFaceInforWidget.h"
#include "AppModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    AppModel* m_model;
    QCameraWidget* m_cameraWidget;
    QWardrobeWidget* m_wardrobeWidget;
    QFaceInforWidget* m_faceInforWidget;
    QStackedWidget* m_stackWidget;

};
#endif // MAINWINDOW_H
