#pragma once

#include <QWidget>
#include "../GuiController/KeyPressController.hpp"

class QKeyEvent;

namespace gui
{

class QControlPanelView : public QWidget
{
    Q_OBJECT;
public:
    explicit QControlPanelView();
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

}  // namespace gui
