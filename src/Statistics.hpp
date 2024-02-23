#pragma once

#include "Types/RobotRemoteControl.pb.h"
#include <string>
#include <sys/time.h>

namespace robot_remote_control {

class Statistics {
 public:
    struct StatData{
        timeval lastCalc;
        timeval initTime;
        int messagesSinceLast;
        double bytesSinceLast;
        double lastBytesSize;
        double bytesTotal;
        double bpsLast;
        double bpsAvg;
        double frequency;
        double frequencyAvg;
        double runningAvgSamples;
    };

    struct Stats {
        explicit Stats(const double &runningAvgSamples = 10);

        void addBytesSent(const double& bytes);

        void calculate(timeval* currenttime);

        void print(const std::string& name);

        const StatData& getStats() {
            return statdata;
        }

        StatData statdata;
        double runningAvgFactor;

     private:
        timeval diff;
    };

    void calculate();

    void print(const bool &verbose = false);

    timeval currenttime;
    Stats global;
    std::array<std::string, TELEMETRY_MESSAGE_TYPES_NUMBER> names;
    std::array<Stats, TELEMETRY_MESSAGE_TYPES_NUMBER> stat_per_type;
};

}  // namespace robot_remote_control
