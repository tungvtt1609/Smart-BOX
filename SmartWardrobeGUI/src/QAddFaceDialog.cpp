#include "QAddFaceDialog.h"
#include "ui_qaddfacedialog.h"

QAddFaceDialog::QAddFaceDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QAddFaceDialog)
{
    ui->setupUi(this);
}

QAddFaceDialog::~QAddFaceDialog()
{
    delete ui;
}
