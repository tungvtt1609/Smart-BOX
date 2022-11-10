#ifndef QADDFACEDIALOG_H
#define QADDFACEDIALOG_H

#include <QWidget>

namespace Ui {
class QAddFaceDialog;
}

class QAddFaceDialog : public QWidget
{
    Q_OBJECT

public:
    explicit QAddFaceDialog(QWidget *parent = nullptr);
    ~QAddFaceDialog();

private:
    Ui::QAddFaceDialog *ui;
};

#endif // QADDFACEDIALOG_H
