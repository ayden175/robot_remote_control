#include "Statistics.hpp"
#include <algorithm>

namespace robot_remote_control {

Statistics::Stats::Stats(const double &runningAvgSamples) {
    statdata.bytesTotal = 0;
    statdata.bytesSinceLast = 0;
    statdata.lastBytesSize = 0;
    statdata.bpsLast = 0;
    statdata.bpsAvg = 0;
    statdata.frequencyAvg = 0;
    statdata.messagesSinceLast = 0;
    gettimeofday(&statdata.lastCalc, 0);
    statdata.runningAvgSamples = runningAvgSamples;
    runningAvgFactor = ((runningAvgSamples-1)/runningAvgSamples);
}


void Statistics::Stats::addBytesSent(const double& bytes) {
    statdata.bytesTotal += bytes;
    statdata.bytesSinceLast += bytes;
    ++statdata.messagesSinceLast;
}

void Statistics::Stats::calculate(timeval* currenttime) {
    timersub(currenttime, &statdata.lastCalc, &diff);
    double seconds = (diff.tv_sec * 1000000 + static_cast<double>(diff.tv_usec))/1000000.0;

    statdata.bpsLast = (statdata.bytesSinceLast/seconds);
    if (statdata.bpsAvg == 0) {
        statdata.bpsAvg = statdata.bpsLast;
    }
    statdata.bpsAvg = (statdata.bpsAvg * runningAvgFactor) + (statdata.bpsLast/statdata.runningAvgSamples);
    statdata.lastCalc = *currenttime;

    if (statdata.bytesSinceLast > 0) {
        statdata.frequency = (1/seconds)*statdata.messagesSinceLast;
        statdata.lastBytesSize = statdata.bytesSinceLast;
    } else {
        statdata.frequency = 0;
    }

    if (statdata.frequencyAvg == 0) {
        statdata.frequencyAvg = statdata.frequency;
    }
    statdata.frequencyAvg = (statdata.frequencyAvg * runningAvgFactor) + (statdata.frequency/statdata.runningAvgSamples);

    statdata.bytesSinceLast = 0;
    statdata.messagesSinceLast = 0;
}

void Statistics::Stats::print(const std::string& name) {
    #ifdef RRC_STATISTICS
        printf("%.2f kBytes/s (size kB: %.2f, freq: %06.2f): %s\n", statdata.bpsAvg/1024.0, statdata.bytesTotal/1024.0, statdata.frequencyAvg, name.c_str());
    #endif
}

void Statistics::calculate() {
    #ifdef RRC_STATISTICS
        gettimeofday(&currenttime, 0);
        global.calculate(&currenttime);
        std::for_each(stat_per_type.begin(), stat_per_type.end(), [&](auto & stat){
            stat.calculate(&currenttime);
        });
    #endif
}

void Statistics::print(const bool &verbose) {
    #ifdef RRC_STATISTICS
        global.print("global");
        if (verbose) {
            for (int i = 1; i < names.size(); ++i) {
                stat_per_type[i].print(names[i]);
            }
        }
    #endif
}



}  // namespace robot_remote_control
