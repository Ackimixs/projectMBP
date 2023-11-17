#pragma once

#include <string>
#include <cstring>

#define __FILENAME__ ( strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __CONTEXT__ ( std::string("[") + __FILENAME__ + ":" + std::to_string(__LINE__) + ":" + __FUNCTION__ + "] ")
