#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

namespace gui
{

struct ConnectionParameters
{
    std::string ip_;
    unsigned int port_;
};

class ConnectionDialog : public QDialog
{
Q_OBJECT;
public:
    explicit ConnectionDialog(QWidget* parent);
    std::optional<ConnectionParameters> getValue() const;
public slots:
    void setPredefinedValue();
private:

    QLineEdit* ipTextBox_;
    QLineEdit* portTextBox_;
    QComboBox* comboBox_;
    QPushButton* okButton_;
    QPushButton* cancelButton_;
};

}  // namespace gui
