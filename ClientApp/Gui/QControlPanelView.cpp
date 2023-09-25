#include "QControlPanelView.hpp"

#include <iostream>

#include <QKeyEvent>
#include <QLabel>

#include <GuiController/KeyPressController.hpp>

namespace gui
{

QControlPanelView::QControlPanelView()
{
    auto label = new QLabel(this);
    label->setText(QString("ControlPanelView"));

    setMinimumSize(320, 240);
    setStyleSheet("background-color:white;color:white;");
    this->setFocusPolicy(Qt::ClickFocus);

    connect(this, &QControlPanelView::changeEvent, [&](auto&&){ std::cout << "Enable changed" << std::endl; });
}

void QControlPanelView::keyPressEvent(QKeyEvent* ev)
{
    std::cout << "[QControlPanelView] Key pressed" << ev->key() << std::endl;

    if (not gui_controller::keyArrowToEnumKey(ev->key()))
    {
        QWidget::keyPressEvent(ev);
        return;
    }

    std::cout << "[QControlPanelView] Key pressed: " << *gui_controller::keyArrowToName(ev->key()) << std::endl;

    QWidget::keyPressEvent(ev);
}

void QControlPanelView::keyReleaseEvent(QKeyEvent *ev)
{
    std::cout << "[QControlPanelView] Key released" << ev->key() << std::endl;

    if (not gui_controller::keyArrowToEnumKey(ev->key()))
    {
        QWidget::keyReleaseEvent(ev);
        return;
    }

    std::cout << "[QControlPanelView] Key released: " << *gui_controller::keyArrowToName(ev->key()) << std::endl;
    QWidget::keyReleaseEvent(ev);
}

} // gui