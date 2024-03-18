#pragma once

#include "Types/RobotRemoteControl.pb.h"


typedef uint8_t MesssageId;  // defines the size of MesssageIds in the protocol (max number of message types)
typedef uint8_t ChannelId;   // defines the size of the channel part of the protocol (and the max number of channels)
typedef uint8_t LogLevelId;  // defines the size of the LogLevel part of the protocol (and the max number of supported log levels)
