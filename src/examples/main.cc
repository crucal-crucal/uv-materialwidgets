#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QFontDatabase>
#include <QResource>

#include "mainwidget.hpp"

bool loadResources(const QString& strPath);
bool unloadResources(const QString& strPath);

int main(int argc, char* argv[]) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
	QApplication app(argc, argv);
	const QFileInfo appFile(QApplication::applicationFilePath());
	// 将路径切换到上级目录
	const QString appParPath = appFile.absolutePath();
	const QString strRcc = appParPath + "/resources.rcc";
	if (loadResources(strRcc)) {
		qInfo() << "load resources success";
	} else {
		qInfo() << "load resources failed";
	}
	QFontDatabase::addApplicationFont(":/fonts/Awesome/CUVAwesome.ttf");

	MainWidget mainWidget;
	QObject::connect(&mainWidget, &MainWidget::destroyed, [&]() {
		unloadResources(strRcc);
	});

	mainWidget.show();

	return QApplication::exec();
}

bool loadResources(const QString& strPath) {
	qDebug() << ("Resource filePath:\t" + strPath);
	return QResource::registerResource(strPath);
}

bool unloadResources(const QString& strPath) {
	if (QResource::unregisterResource(strPath)) {
		qDebug() << "unregister resource success";
		return true;
	}
	return false;
}
