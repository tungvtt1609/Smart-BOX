#ifndef QFACEINFORWIDGET_H
#define QFACEINFORWIDGET_H

#include <QWidget>
#include "AppModel.h"

namespace Ui {
class QFaceInforWidget;
}

class QFaceInforWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QFaceInforWidget(QWidget *parent = nullptr, AppModel* model = nullptr);
    ~QFaceInforWidget();
    void loadFaceInfor1();
    void loadFaceInfor2();
    void loadFaceInfor3();
    void loadFaceInfor4();

private:
    Ui::QFaceInforWidget *ui;
    AppModel* m_model;
};

#endif // QFACEINFORWIDGET_H
