#ifndef APPCONSTANTS_H
#define APPCONSTANTS_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QColor>
#include <QMutex>
#include <QCoreApplication>

#ifndef MACRO_DEFINE
#define MACRO_DEFINE

#define CONSOLE qDebug() << "[" << __FUNCTION__ << "] "

#endif

#ifndef BUILD_DIR

#define BUILD_DIR QCoreApplication::applicationDirPath()

#endif

#define DB_PATH "./data/wardrobe.db"

#define AVAILABLE_SLOT "./data/res/open-box.png"
#define UNAVAILABLE_SLOT "./data/res/archive.png"

#define FACE_CASCADE "./data/haarcascade_frontalface_alt.xml"
#define FACE_IMAGE "/data/face_db/"
#define EIGEN_FACE "./data/model/eigenface.yml"
#define IMAGE_TEST "./data/face_db/2/00004.png"

#define PLUGINS_SUBFOLDER "/Plugins/"

#define BACKGOUND ":/images/data/res/background.jpg"
#define APP_ICON ":/images/data/res/icon.png"

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

#endif // APPCONSTANTS_H
