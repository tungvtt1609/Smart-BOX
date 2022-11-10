#include "QWardrobeWidget.h"
#include "ui_qwardrobewidget.h"
#include "AppConstants.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSvgRenderer>
#include <QPainter>
#include <QImage>

QWardrobeWidget::QWardrobeWidget(QWidget *parent, AppModel *model) :
    QWidget(parent),
    ui(new Ui::QWardrobeWidget)
{
    ui->setupUi(this);
    m_model = model;

    updateUI();
}

QWardrobeWidget::~QWardrobeWidget()
{
    delete ui;
}

void QWardrobeWidget::updateUI()
{
    QSqlQuery query(m_model->m_database->getDBInstance());
    query.prepare("select slot, available from wardrobe");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
    }
    else{
        qDebug() << "read was successful "<< query.lastQuery();
    }

    while(query.next())
    {
        QString sLabel = query.value(0).toString();
        qDebug() <<"label is : "<< sLabel;
        QLabel * ptr = this->findChild<QLabel*>(sLabel);
        if(ptr!=nullptr)
        {   qDebug() << "label found "<<sLabel;
            if(query.value(1).toString().compare("N") == 0)
            {
//                QSvgRenderer renderer(QString(UNAVAILABLE_SLOT));
//                // Prepare a QImage with desired characteritisc
//                QImage image(ptr->width(), ptr->height(), QImage::Format_ARGB32);
//                image.fill(0xaaA08080);  // partly transparent red-ish background
//                // Get QPainter that paints to the image
//                QPainter painter(&image);
//                renderer.render(&painter);

//                QPixmap pm = QPixmap::fromImage(image);
                QPixmap pm(UNAVAILABLE_SLOT);
                ptr->setPixmap(pm.scaled(230,190,Qt::KeepAspectRatio,Qt::FastTransformation));
                ptr->setScaledContents(true);
                qDebug()<<query.value(0).toString() << " : is Unavaiable";
            }
            else
            {
//                QSvgRenderer renderer(QString(AVAILABLE_SLOT));
//                // Prepare a QImage with desired characteritisc
//                QImage image(ptr->width(), ptr->height(), QImage::Format_ARGB32);
//                image.fill(0xaaA08080);  // partly transparent red-ish background
//                // Get QPainter that paints to the image
//                QPainter painter(&image);
//                renderer.render(&painter);

//                QPixmap pm = QPixmap::fromImage(image);

                QPixmap pm(AVAILABLE_SLOT);
                ptr->setPixmap(pm.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation));
                ptr->setScaledContents(true);
                qDebug()<<query.value(0).toString() << " : is Available";
            }

        }
    }
}
