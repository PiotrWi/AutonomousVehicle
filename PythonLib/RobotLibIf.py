from ctypes import *
from time import sleep


def react_on_change(con_status):
    print ("connection status: {}".format(con_status))


class Speed(Structure):
    _fields_ = ("leftWheel", c_int), ("rightWheel", c_int)


class RobotHandler:
    def __init__(self):
        self.if_handler = cdll.LoadLibrary("/home/pioter/proj/AuthonomousVehicle/cmake-build-debug/RobotClientLib/libAutonomousVehicleInterface.so")

    def init(self):
        # TODO: tmp until proper installation is done
        self.if_handler.c_init()

    def connect(self) -> bool:
        return bool(self.if_handler.c_connect())

    def disconnect(self):
        self.if_handler.c_disconnect()

    def is_connected(self) -> bool:
        return bool(self.if_handler.c_isConnected())

    def subscribe_for_connection_status(self, func):
        callback_fun = CFUNCTYPE(None, c_bool)
        self.if_handler.c_subscribeForConnectionStatus(callback_fun(func))

    def set_speed(self, leftWheel, rightWheel):
        s = Speed(leftWheel, rightWheel)
        self.if_handler.c_setRequestedSpeed(s)

    def get_speed(self) -> (int, int):
        s = Speed(self.if_handler.c_getRequestedSpeed());
        return (s.leftWheel, s.rightWheel)

    def subscribe_for_speed_change(self, func):
        callback_fun = CFUNCTYPE(None, c_bool)
        self.if_handler.c_subscribeForConnectionStatus(callback_fun(func))


handler = RobotHandler()
handler.init()
handler.subscribe_for_connection_status(react_on_change)
handler.connect()
sleep(3)
is_connected = handler.is_connected()
print(type(is_connected))
print(is_connected)

handler.set_speed(10, 10)

handler.disconnect()

