﻿#include "info_window.h"
#include "define.h"
#include "pixelfont.h"

#include <windows.h>
#include <QPropertyAnimation>

/**
 * \brief 信息提示框
 * \param content 
 * \param btn_count 
 * \param parent 
 */
InfoWindow::InfoWindow(const QString& content, const int btn_count, QWidget *parent) : QDialog(parent) {
	// 设置窗口颜色
	auto pal = palette();
	pal.setColor(QPalette::Background, DARK_COLOR);
	setAutoFillBackground(true);
    setPalette(pal);

	// 无边框模式
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	// 失焦闪烁功能
	connect(this, &InfoWindow::ncActive, this, &InfoWindow::flashWindow);

	// 内容文字
	label_content = new QLabel(content, this);
	label_content->setFont(PixelFont("Microsoft YaHei UI", 12, 50));
	label_content->setStyleSheet("QLabel { color: rgb(204, 204, 204) }");

	// 按钮布局
	layout_btn = new QHBoxLayout;
	layout_btn->setSpacing(SPACING_SMALL);

	switch (btn_count) {
		case 1:
			btn_control_1 = new MenuButton(tr("返回"), this, true);
			label_game_name = new QLabel(tr(R"(<font color="#cccccc">Nono</font><font color="#FF7800">gram</font>)"), this);
			label_game_name->setFont(PixelFont("Berlin Sans FB", 25, 50));
			layout_btn->addWidget(label_game_name, 0, Qt::AlignCenter);
			layout_btn->addStretch();
			layout_btn->addWidget(btn_control_1, 0, Qt::AlignCenter);
			break;
		case 2:
			btn_control_1 = new MenuButton(tr("确定"), this, true);
			btn_control_2 = new MenuButton(tr("取消"), this, true);
			btn_control_2->setDefault(true);
			layout_btn->addStretch();
			layout_btn->addWidget(btn_control_1, 0, Qt::AlignCenter);
			layout_btn->addWidget(btn_control_2, 0, Qt::AlignCenter);
			layout_btn->addStretch();
			btn_control_2->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
			connect(btn_control_2, &QPushButton::clicked, this, &InfoWindow::btnControl2Clicked);
			break;
		case 3:
			btn_control_1 = new MenuButton(tr("保存"), this, true);
			btn_control_2 = new MenuButton(tr("不保存"), this, true);
			btn_control_3 = new MenuButton(tr("取消"), this, true);
			btn_control_1->setDefault(true);
			layout_btn->addStretch();
			layout_btn->addWidget(btn_control_1, 0, Qt::AlignCenter);
			layout_btn->addWidget(btn_control_2, 0, Qt::AlignCenter);
			layout_btn->addWidget(btn_control_3, 0, Qt::AlignCenter);
			layout_btn->addStretch();
			btn_control_2->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
			btn_control_3->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
			connect(btn_control_2, &QPushButton::clicked, this, &InfoWindow::btnControl2Clicked);
			connect(btn_control_3, &QPushButton::clicked, this, &InfoWindow::btnControl3Clicked);
		default: ;
	}
	btn_control_1->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
	connect(btn_control_1, &QPushButton::clicked, this, &InfoWindow::btnControl1Clicked);

	layout_this = new QVBoxLayout;
	setLayout(layout_this);
	layout_this->addWidget(label_content, 0, Qt::AlignCenter);
	layout_this->addLayout(layout_btn);
	layout_this->setContentsMargins(40, 15, 40, 15);
	layout_this->setSpacing(2 * SPACING_LARGE);
}

/**
 * \brief 控制按钮一按下
 */
void InfoWindow::btnControl1Clicked() {
	done(Accepted);
}

/**
 * \brief 控制按钮二按下
 */
void InfoWindow::btnControl2Clicked() {
	done(Rejected);
}

/**
 * \brief 控制按钮三按下
 */
void InfoWindow::btnControl3Clicked() {
	done(3);
}

/**
 * \brief 移动无边框窗口
 * \param event 
 */
void InfoWindow::mousePressEvent(QMouseEvent *event) {
	if (ReleaseCapture()) {
		SendMessage(HWND(this->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
	}
	event->ignore();
}

/**
 * \brief 微调位置和淡入效果
 * 
 * 该函数未在非“1080p 100%缩放”的显示器上测试过，可能会出现显示问题
 * \param event 
 */
void InfoWindow::showEvent(QShowEvent *event) {
	QDialog::showEvent(event);
	move(geometry().x() + 8, geometry().y());
	// ReSharper disable once CppNonReclaimedResourceAcquisition
	auto anim = new QPropertyAnimation(this, "windowOpacity");
	anim->setStartValue(0.0);
	anim->setEndValue(1.0);
	anim->setDuration(120);
	anim->start(QAbstractAnimation::DeleteWhenStopped);
}

/**
 * \brief 窗口失焦闪烁信号
 * \param event_type 
 * \param message 
 * \param result 
 * \return 
 */
bool InfoWindow::nativeEvent(const QByteArray& event_type, void* message, long* result) {
	const auto msg = static_cast<MSG*>(message);
    if(msg->message == WM_NCACTIVATE) {
		emit ncActive(static_cast<bool>(msg->wParam));
    }
	return QWidget::nativeEvent(event_type, message, result);
}

/**
 * \brief 窗口失焦闪烁效果
 * \param active 
 */
void InfoWindow::flashWindow(const bool active) {
	if (active) {
		setStyleSheet("QDialog { border: 2px solid rgb(255, 120, 0); background-color: rgb(43, 43, 43) }");
	} else {
		setStyleSheet("QDialog { border: 3px solid rgb(255, 120, 0); background-color: rgb(43, 43, 43) }");
	}
}

/**
 * \brief 析构函数
 */
InfoWindow::~InfoWindow() {
	delete layout_btn;
    layout_btn = nullptr;
	delete layout_this;
	layout_this = nullptr;
}