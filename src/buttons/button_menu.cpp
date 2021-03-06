﻿#include "src/buttons/button_menu.h"
#include "src/utils/util_generic_define.h"
#include "src/utils/util_pixel_font.h"

/**
 * \brief 菜单按钮构造函数
 * \param caption 按钮文字
 * \param parent 父部件指针
 * \param accent_color 是否上高亮色
 */
MenuButton::MenuButton(const QString& caption, QWidget* parent, const bool accent_color)
		: QPushButton(caption, parent) {
    setFont(PixelFont("Microsoft YaHei UI", BUTTON_FONT_SIZE, 75));
    setFocusPolicy(Qt::NoFocus);
    setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    if (accent_color) {
        setStyleSheet(
            "QPushButton {"
                "color: rgb(43, 43, 43);"
                "border: 2px solid #555555;"
                "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(255, 150, 0), stop:0.50001 rgb(214, 214, 214));"
                "border-radius:1px;"
            "}"
            "QPushButton:hover {"
                "border: 2px solid #FF7800;"
                "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(255, 160, 70), stop:0.50001 rgb(240, 230, 190));"
            "}"
            "QPushButton:disabled {"
                "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(154, 154, 154), stop:0.50001 rgb(174, 174, 174));"
            "}"
            "QPushButton:pressed {"
                "border: 2px solid #FF7800;"
                "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(200, 125, 60), stop:0.50001 rgb(205, 170, 140));"
            "}"
        );
    } else {
        setStyleSheet(
            "QPushButton {"
                "color: rgb(43, 43, 43);"
                "border: 2px solid #555555;"
                "background-color: rgb(214, 214, 214);"
                "border-radius:1px;"
            "}"
            "QPushButton:hover {"
                "border: 2px solid #FF7800;"
                "background-color: rgb(240, 230, 190);"
            "}"
            "QPushButton:pressed {"
                "border: 2px solid #FF7800;"
                "background-color: rgb(205, 170, 140);"
            "}"
            "QPushButton:default {"
                "border: 2px solid #FF7800;"
                "background-color: rgb(214, 214, 214);"
            "}"
            "QPushButton:default:hover {"
                "border: 2px solid #FF7800;"
                "background-color: rgb(240, 230, 190);"
            "}"
            "QPushButton:default:pressed {"
                "border: 2px solid #FF7800;"
                "background-color: rgb(205, 170, 140);"
            "}"
        );
    }
}
