#pragma once

#include <QSize>

namespace rps::infrastructure::util
{

inline constexpr QSize kMaxButtonSize{320, 90};

inline constexpr const char* kDefaultGreenButtonStyle =
    "QPushButton {"
    "background-color:rgb(76, 175, 80);"
    "color: white;"
    "border: none;"
    "border-radius: 10px;"
    "padding: 10px;"
    "font-size: 16px;"
    "font-weight: bold;"
    "}"
    "QPushButton:hover {"
    "background-color:rgb(46, 199, 54);"
    "}"
    "QPushButton:pressed {"
    "background-color:rgb(46, 199, 54);"
    "}";

inline constexpr const char* kDefaultRedButtonStyle =
    "QPushButton {"
    "background-color:rgb(156, 76, 71);"
    "color: white;"
    "border: none;"
    "border-radius: 10px;"
    "padding: 10px;"
    "font-size: 16px;"
    "font-weight: bold;"
    "}"
    "QPushButton:hover {"
    "background-color:rgb(184, 42, 42);"
    "}"
    "QPushButton:pressed {"
    "background-color:rgb(184, 42, 42);"
    "}";

inline constexpr const char* kDefaultLineEditStyle =
    "QLineEdit {"
    "border: 4px solid #4CAF50;"
    "border-radius: 10px;"
    "padding: 10px;"
    "font-size: 16px;"
    "font-weight: bold;"
    "background-color: #f9f9f9;"
    "color: #333;"
    "}"
    "QLineEdit:focus {"
    "border: 4px solid #45a049;"
    "background-color: #fff;"
    "}";

} // namespace rps::infrastructure::util
