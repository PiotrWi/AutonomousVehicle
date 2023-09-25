#include "QLadarVier.hpp"

#include <QLabel>

namespace gui
{

QLadarView::QLadarView()
{
    auto label = new QLabel(this);
    label->setText(QString("LadarView"));
    setMinimumSize(320, 240);
    setStyleSheet("background-color:blue;color:white;");
}

}  // namespace gui
