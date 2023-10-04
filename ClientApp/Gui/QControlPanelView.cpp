#include "QControlPanelView.hpp"

#include <iostream>

#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

#include <GuiController/KeyPressController.hpp>

namespace gui
{

QControlPanelView::QControlPanelView()
    : keyPressController_(gui_controller::KeyPressController::getInstance())
{
    setMinimumSize(320, 240);

    this->setFocusPolicy(Qt::ClickFocus);

    createSpeedsWidgets();
    connectSpeedWidgetsToSpeedChanges();

    connect(this, &QControlPanelView::changeEvent, [&](auto&&)
    {
        if (isEnabled() && isStarted_ != isEnabled())
        {
            std::cout << "QControlPanelView is enabled" << std::endl;
            start();
        }
        else if(not isEnabled() && isStarted_ != not isEnabled())
        {
            std::cout << "QControlPanelView is disabled" << std::endl;
            stop();
        }
    });
}

void QControlPanelView::keyPressEvent(QKeyEvent* ev)
{
    std::cout << "[QControlPanelView] Key pressed" << ev->key() << std::endl;

    auto key = gui_controller::keyArrowToEnumKey(ev->key());
    if (not key)
    {
        QWidget::keyPressEvent(ev);
        return;
    }

    std::cout << "[QControlPanelView] Key pressed: " << *gui_controller::keyArrowToName(ev->key()) << std::endl;
    keyPressController_.setKeyClicked(*key);

    QWidget::keyPressEvent(ev);
}

void QControlPanelView::keyReleaseEvent(QKeyEvent *ev)
{
    std::cout << "[QControlPanelView] Key released" << ev->key() << std::endl;

    auto key = gui_controller::keyArrowToEnumKey(ev->key());
    if (not key)
    {
        QWidget::keyReleaseEvent(ev);
        return;
    }

    std::cout << "[QControlPanelView] Key released: " << *gui_controller::keyArrowToName(ev->key()) << std::endl;
    keyPressController_.setKeyReleased(*key);

    QWidget::keyReleaseEvent(ev);
}

void QControlPanelView::start()
{
    keyPressController_.start();
}

void QControlPanelView::stop()
{
    keyPressController_.stop();
}

void QControlPanelView::createSpeedsWidgets()
{
    QWidget* widgetWithSpeeds = new QWidget(this);
    QFormLayout* form = new QFormLayout;

    requestedLeftWheelSpeedLabel_ = new QLabel(this);
    requestedLeftWheelSpeedLabel_->setText("Left wheel speed: ");
    requestedLeftWheelSpeedOut_ = new QLineEdit(this);
    requestedLeftWheelSpeedOut_->setReadOnly(true);

    requestedRightWheelSpeedLabel_ = new QLabel(this);
    requestedRightWheelSpeedLabel_->setText("Left wheel speed: ");
    requestedRightWheelSpeedOut_ = new QLineEdit(this);
    requestedRightWheelSpeedOut_->setReadOnly(true);

    form->addRow(requestedLeftWheelSpeedLabel_, requestedLeftWheelSpeedOut_);
    form->addRow(requestedRightWheelSpeedLabel_, requestedRightWheelSpeedOut_);

    widgetWithSpeeds->setLayout(form);
    fullfillSpeeds();
}

void QControlPanelView::fullfillSpeeds()
{
    auto speeds = keyPressController_.getCurrentSetSpeeds();
    requestedLeftWheelSpeedOut_->setText(QString::number(speeds.leftMotorSpeed_));
    requestedRightWheelSpeedOut_->setText(QString::number(speeds.rightMotorSpeed_));
}

void QControlPanelView::connectSpeedWidgetsToSpeedChanges()
{
    keyPressController_.subscribeToSpeeds([this](auto speeds) {
        emit requestedSpeedChanged(speeds);
    });
    connect(this, &QControlPanelView::requestedSpeedChanged, [this](){
        fullfillSpeeds();
    });
}

} // gui
