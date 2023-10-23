#include "ConnectionDialog.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

namespace
{

bool validateIp(std::string)
{
    return true;
}

}  // namespace

namespace gui
{

ConnectionDialog::ConnectionDialog(QWidget *parent)
    : QDialog(parent)
    , ipTextBox_(new QLineEdit())
    , portTextBox_(new QLineEdit())
{
    auto gridLayout = new QGridLayout();

    gridLayout->addWidget(new QLabel("IP: "), 0, 0);
    gridLayout->addWidget(ipTextBox_, 0, 1);
    gridLayout->addWidget(new QLabel("PORT: "), 1, 0);
    gridLayout->addWidget(portTextBox_, 1, 1);

    gridLayout->addWidget(new QLabel("Predefined: "), 2, 0);
    comboBox_ = new QComboBox();
    comboBox_->addItem("127.0.0.1:17831");
    comboBox_->addItem("172.16.1.64:17831");
    connect(comboBox_, &QComboBox::activated, this, &ConnectionDialog::setPredefinedValue);

    gridLayout->addWidget(comboBox_, 2, 1);

    okButton_ = new QPushButton("OK");
    connect(okButton_, &QPushButton::clicked, this, &ConnectionDialog::accept);
    gridLayout->addWidget(okButton_,3, 0);

    cancelButton_ = new QPushButton("CANCEL");
    connect(cancelButton_, &QPushButton::clicked, this, &ConnectionDialog::reject);
    gridLayout->addWidget(cancelButton_,3, 1);

    this->setLayout(gridLayout);
}

std::optional<ConnectionParameters> ConnectionDialog::getValue() const
{
    bool status;
    ConnectionParameters connectionParameters;
    connectionParameters.ip_ = ipTextBox_->text().toStdString();
    connectionParameters.port_ = portTextBox_->text().toInt(&status);
    status &= validateIp(connectionParameters.ip_);
    if (not status)
    {
        QMessageBox alert;
        alert.setText("Parse error");
        alert.exec();
        return {};
    }
    return connectionParameters;
}

void ConnectionDialog::setPredefinedValue()
{
    auto text = comboBox_->currentText();
    auto values = text.split(':');

    ipTextBox_->setText(values.front());
    portTextBox_->setText(values.back());
}

}  // namespace gui
