﻿#include "controller_version.h"

const QString VersionController::VERSION_NUMBER = QString("2.7.5.0");

const QDate VersionController::BUILD_DATE = QLocale(QLocale::English).toDate(QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");

const QTime VersionController::BUILD_TIME = QTime::fromString(__TIME__, "hh:mm:ss");

const bool VersionController::RELEASE_STATE = false;

QString VersionController::getVersion() {
	const QString release_string = RELEASE_STATE ? "Release" : "Debug";
    return QString("%1 (build %2) %3").arg(VERSION_NUMBER).arg(BUILD_NUMBER).arg(release_string);
}

QString VersionController::getBulidDateTime() {
    return BUILD_DATE.toString("yyyy年M月d日") + " " + BUILD_TIME.toString();
}