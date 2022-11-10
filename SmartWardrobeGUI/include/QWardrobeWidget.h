#ifndef QWARDROBEWIDGET_H
#define QWARDROBEWIDGET_H

#include <QWidget>
#include "AppModel.h"

namespace Ui {
class QWardrobeWidget;
}

/* Display the state of wardrobe */

class QWardrobeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QWardrobeWidget(QWidget *parent = nullptr, AppModel *model = nullptr);
    ~QWardrobeWidget();

    void updateUI();

private:
    Ui::QWardrobeWidget *ui;
    AppModel* m_model;
};

#endif // QWARDROBEWIDGET_H
