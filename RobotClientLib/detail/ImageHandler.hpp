#pragma once

#include <functional>
#include <map>
#include <mutex>

#include "Types.hpp"
#include "IMessageHandler.hpp"


class ImageHandler : public IMessageHandler
{
public:
    void handle(const std::string& message) override;
    std::string getPrefix() override;
    void clear() override;

    robot_interface::IntegerPicture getImage(robot_interface::CameraSide side);
    void subscribeForPicture(robot_interface::CameraSide, std::function<void(robot_interface::IntegerPicture)> callback);
private:
    std::mutex contentMutex_;
    std::map<
        robot_interface::CameraSide,
        std::pair<
            std::function<void(robot_interface::IntegerPicture)>,
            robot_interface::IntegerPicture>> content_;
};
