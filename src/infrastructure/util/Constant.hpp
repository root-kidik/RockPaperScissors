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
    "background-color:rgb(28, 119, 32);"
    "}"
    "QPushButton:pressed {"
    "background-color:rgb(28, 119, 32);"
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
    "background-color:rgb(121, 26, 26);"
    "}"
    "QPushButton:pressed {"
    "background-color:rgb(121, 26, 26);"
    "}";

inline constexpr const char* kDefaultGreenLabelStyle =
    "QLabel {"
    "background-color: transparent;"
    "color: rgb(76, 175, 80);"
    "border: none;"
    "border-radius: 10px;"
    "padding: 10px;"
    "font-size: 24px;"
    "font-weight: bold;"
    "text-align: center;"
    "}";

inline constexpr const char* kDefaultRedLabelStyle =
    "QLabel {"
    "background-color: transparent;"
    "color: rgb(156, 76, 71);"
    "border: none;"
    "border-radius: 10px;"
    "padding: 10px;"
    "font-size: 24px;"
    "font-weight: bold;"
    "text-align: center;"
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
