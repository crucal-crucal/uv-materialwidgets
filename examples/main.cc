﻿#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QFontDatabase>
#include <QResource>

#include "mainwidget.hpp"

/**
 * 加载 rcc
 * @param strPath rcc 文件路径
 * @return true 加载成功 false 加载失败
 */
bool loadResources(const QString& strPath);
/**
 * 卸载 rcc
 * @param strPath rcc 文件路径
 * @return true 卸载成功 false 卸载失败
 */
bool unloadResources(const QString& strPath);

int main(int argc, char* argv[]) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
	// 启用高 DPI 缩放
	qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");

	// 设置高 DPI 将缩放因子四舍五入到最接近的整数
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);
#else
#warning "The current Qt version does not support QT_ENABLE_HIGHDPI_SCALING or HighDpiScaleFactorRoundingPolicy. Please ensure you are using Qt 5.14 or newer."
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

	if (QFontDatabase::addApplicationFont(":/fonts/cuvawesome") != -1) {
		qInfo() << "add font success";
	} else {
		qWarning() << "add font failed";
	}

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
