#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <time.h>

#include <QString>

#include "adapter.h"
#include "myo/myo.hpp"

class Adapter;

class DataCollector : public myo::DeviceListener
{
public:
    DataCollector(Adapter *ad);

    void openFiles();
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);
    void onOrientationData(myo::Myo *myo, uint64_t timestamp, const myo::Quaternion< float > &rotation);
    void onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel);
    void onGyroscopeData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &gyro);
    void onConnect(myo::Myo *myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    void onPair (myo::Myo *myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    void onUnpair (myo::Myo *myo, uint64_t timestamp);
    void onArmSync (myo::Myo *myo, uint64_t timestamp, myo::Arm arm,
                    myo::XDirection xDirection, float rotation, myo::WarmupState warmupState);
    void onArmUnsync (myo::Myo *myo, uint64_t timestamp);
    void onUnlock (myo::Myo *myo, uint64_t timestamp);
    void onLock (myo::Myo *myo, uint64_t timestamp);
    void onWarmupCompleted (myo::Myo *myo, uint64_t timestamp, myo::WarmupResult warmupResult);
    void onBatteryLevelReceived (myo::Myo *myo, uint64_t timestamp, uint8_t level);

    void onPose (myo::Myo *myo, uint64_t timestamp, myo::Pose pose);

    volatile void setLoggingFlag(bool flag);
    void setEvent(QString event);
    QString getEvent();

private:
    volatile bool loggingFlag = false;
    QString event;
    Adapter *ad;

    std::ofstream emgFile;
    std::ofstream gyroFile;
    std::ofstream orientationFile;
    std::ofstream orientationEulerFile;
    std::ofstream accelerometerFile;

    void printVector(std::ofstream &file, uint64_t timestamp, const myo::Vector3< float > &vector);
    char* fevent(char* str);
};

#endif // DATACOLLECTOR_H
