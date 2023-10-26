#include "GpioDriverBase.hpp"

namespace drivers
{

const char *GpioLocation = "/sys/class/gpio";
const char *GpioExportLocation = "/sys/class/gpio/export";
const char *GpioUnexportLocation = "/sys/class/gpio/unexport";

}  // namespace drivers
