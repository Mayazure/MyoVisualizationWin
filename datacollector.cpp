#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QDebug>

#include "datacollector.h"
//#include <iostream>
//using namespace std;

DataCollector::DataCollector(Adapter *ad)
{
    this->ad=ad;
    //    openFiles();
}

void DataCollector::onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{
    static int emgData[8];
//    static uint64_t lastTimestamp = 0;
    static int index = 0;//kept for debug

//    if(lastTimestamp!=timestamp){
//        lastTimestamp=timestamp;
//        index = 0;
//    }
//    else if(index>1){
//        index = 0;
//        static int i=0;
//        qDebug()<<i<<"index>1";
//        i++;
//    }

    if(loggingFlag){
        emgFile << timestamp << ',';
        QByteArray temp = event.toLatin1();
        char* eventChar = temp.data();
        emgFile << eventChar;

        for (size_t i = 0; i < 8; i++) {
            emgFile << ',' << static_cast<int>(emg[i]);
            emgData[i] = emg[i];

        }
        emgFile << std::endl;
        ad->updateTotalNum(0);

        //        ad->updateGraph(emgData,emg[0],emg[1],emg[2],emg[3],emg[4],emg[5],emg[6],emg[7]);
        //        qDebug()<<a[0];
    }
    ad->updateGraph(index, emgData,emg[0],emg[1],emg[2],emg[3],emg[4],emg[5],emg[6],emg[7]);
//    index++;
}

void DataCollector::onOrientationData(myo::Myo *myo, uint64_t timestamp, const myo::Quaternion< float > &rotation) {

    if(loggingFlag){
        QByteArray temp = event.toLatin1();
        char* eventChar = temp.data();
        orientationFile << timestamp
                        << ',' << eventChar
                        << ',' << rotation.x()
                        << ',' << rotation.y()
                        << ',' << rotation.z()
                        << ',' << rotation.w()
                        << std::endl;

        using std::atan2;
        using std::asin;
        using std::sqrt;
        using std::max;
        using std::min;

        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        float roll = atan2(2.0f * (rotation.w() * rotation.x() + rotation.y() * rotation.z()),
                           1.0f - 2.0f * (rotation.x() * rotation.x() + rotation.y() * rotation.y()));
        float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (rotation.w() * rotation.y() - rotation.z() * rotation.x()))));
        float yaw = atan2(2.0f * (rotation.w() * rotation.z() + rotation.x() * rotation.y()),
                          1.0f - 2.0f * (rotation.y() * rotation.y() + rotation.z() * rotation.z()));
        ad->updateTotalNum(3);

        orientationEulerFile << timestamp
                             << ',' << eventChar
                             << ',' << roll
                             << ',' << pitch
                             << ',' << yaw
                             << std::endl;
        ad->updateTotalNum(4);
    }


    using std::atan2;
    using std::asin;
    using std::sqrt;
    using std::max;
    using std::min;
    float roll = atan2(2.0f * (rotation.w() * rotation.x() + rotation.y() * rotation.z()),
                       1.0f - 2.0f * (rotation.x() * rotation.x() + rotation.y() * rotation.y()));
    float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (rotation.w() * rotation.y() - rotation.z() * rotation.x()))));
    float yaw = atan2(2.0f * (rotation.w() * rotation.z() + rotation.x() * rotation.y()),
                      1.0f - 2.0f * (rotation.y() * rotation.y() + rotation.z() * rotation.z()));

//    ad->updateGyro(roll,pitch,yaw);
    ad->updateGyro(rotation.x(),rotation.y(),rotation.z());

}

// onAccelerometerData is called whenever new acceleromenter data is provided
// Be warned: This will not make any distiction between data from other Myo armbands
void DataCollector::onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel) {

    if(loggingFlag){
        printVector(accelerometerFile, timestamp, accel);
        ad->updateTotalNum(2);
    }
//    ad->updateGyro(accel.x(),accel.y(),accel.z());
}

// onGyroscopeData is called whenever new gyroscope data is provided
// Be warned: This will not make any distiction between data from other Myo armbands
void DataCollector::onGyroscopeData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &gyro) {
    if(loggingFlag){
        printVector(gyroFile, timestamp, gyro);
        ad->updateTotalNum(1);
    }

//    ad->updateGyro(gyro.x(),gyro.y(),gyro.z());
}

void DataCollector::onConnect(myo::Myo *myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    myo->setStreamEmg(myo::Myo::streamEmgEnabled);
    openFiles();
    //    qDebug() << "onConnect";
    QString version = QString::number(firmwareVersion.firmwareVersionMajor);
    version+=".";
    version+=QString::number(firmwareVersion.firmwareVersionMinor);
    version+=".";
    version+=QString::number(firmwareVersion.firmwareVersionPatch);
    ad->updateConsole("Version: "+version);
}

void DataCollector::onPair(myo::Myo *myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    ad->updateConsole(QString::number(timestamp)+": Pair.");
}

void DataCollector::onUnpair(myo::Myo *myo, uint64_t timestamp)
{
    ad->updateConsole(QString::number(timestamp)+": unPair.");
}

void DataCollector::onArmSync(myo::Myo *myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation, myo::WarmupState warmupState)
{
    ad->updateConsole(QString::number(timestamp)+": ArmSync.");
}

void DataCollector::onArmUnsync(myo::Myo *myo, uint64_t timestamp)
{
    ad->updateConsole(QString::number(timestamp)+": ArmUnsync.");
}

void DataCollector::onUnlock(myo::Myo *myo, uint64_t timestamp)
{
    ad->updateConsole(QString::number(timestamp)+": Unlock.");
}

void DataCollector::onLock(myo::Myo *myo, uint64_t timestamp)
{
    ad->updateConsole(QString::number(timestamp)+": Lock.");
}

void DataCollector::onWarmupCompleted(myo::Myo *myo, uint64_t timestamp, myo::WarmupResult warmupResult)
{
    ad->updateConsole(QString::number(timestamp)+": WarmupCompleted.");
}

void DataCollector::onBatteryLevelReceived(myo::Myo *myo, uint64_t timestamp, uint8_t level)
{
    //    ad->updateConsole("Battery: "+QString::number(level)+"%");
    ad->updateBattery(level);
}

void DataCollector::onPose(myo::Myo *myo, uint64_t timestamp, myo::Pose pose)
{
    if (pose != myo::Pose::unknown && pose != myo::Pose::rest) {
        // Tell the Myo to stay unlocked until told otherwise. We do that here so you can hold the poses without the
        // Myo becoming locked.
        myo->unlock(myo::Myo::unlockHold);
        // Notify the Myo that the pose has resulted in an action, in this case changing
        // the text on the screen. The Myo will vibrate.
        myo->notifyUserAction();
    } else {
        // Tell the Myo to stay unlocked only for a short period. This allows the Myo to stay unlocked while poses
        // are being performed, but lock after inactivity.
        myo->unlock(myo::Myo::unlockTimed);
    }
    ad->updateConsole(QString::fromStdString(pose.toString()));
}

volatile void DataCollector::setLoggingFlag(bool flag)
{
    this->loggingFlag = flag;
}

void DataCollector::setEvent(QString event)
{
    this->event = event;
}

QString DataCollector::getEvent()
{
    return event;
}

void DataCollector::openFiles(){

    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/MyoRecording";
    QDir dir(dirPath);
    if(!dir.exists())
    {
        dir.mkdir(dirPath);
    }

    QDateTime time = QDateTime::currentDateTime();
    QString timename = time.toString("yyyyMMddhhmmss");
    dirPath += "/" + timename;
    QDir dir1(dirPath);
    if(!dir1.exists())
    {
        dir1.mkdir(dirPath);
    }

    ad->setPath(dirPath, timename);
    QByteArray temp = dirPath.toLatin1();
    char *filePath = temp.data();
    QByteArray temp1 = timename.toLatin1();
    char *fileName = temp1.data();


    // Open file for EMG log
    if (emgFile.is_open()) {
        emgFile.close();
    }
    std::ostringstream emgFileString;
    emgFileString << filePath << "\\emg-" << fileName << ".csv";
    emgFile.open(emgFileString.str(), std::ios::out);
    emgFile << "timestamp,event,emg1,emg2,emg3,emg4,emg5,emg6,emg7,emg8" << std::endl;

    // Open file for gyroscope log
    if (gyroFile.is_open()) {
        gyroFile.close();
    }
    std::ostringstream gyroFileString;
    gyroFileString << filePath << "\\gyro-" << fileName << ".csv";
    gyroFile.open(gyroFileString.str(), std::ios::out);
    gyroFile << "timestamp,event,x,y,z" << std::endl;

    // Open file for accelerometer log
    if (accelerometerFile.is_open()) {
        accelerometerFile.close();
    }
    std::ostringstream accelerometerFileString;
    accelerometerFileString << filePath << "\\accelerometer-" << fileName << ".csv";
    accelerometerFile.open(accelerometerFileString.str(), std::ios::out);
    accelerometerFile << "timestamp,event,x,y,z" << std::endl;

    // Open file for orientation log
    if (orientationFile.is_open()) {
        orientationFile.close();
    }
    std::ostringstream orientationFileString;
    orientationFileString << filePath << "\\orientation-" << fileName << ".csv";
    orientationFile.open(orientationFileString.str(), std::ios::out);
    orientationFile << "timestamp,event,x,y,z,w" << std::endl;

    // Open file for orientation (Euler angles) log
    if (orientationEulerFile.is_open()) {
        orientationEulerFile.close();
    }
    std::ostringstream orientationEulerFileString;
    orientationEulerFileString << filePath << "\\orientationEuler-" << fileName << ".csv";
    orientationEulerFile.open(orientationEulerFileString.str(), std::ios::out);
    orientationEulerFile << "timestamp,event,roll,pitch,yaw" << std::endl;
}

void DataCollector::printVector(std::ofstream &file, uint64_t timestamp, const myo::Vector3< float > &vector) {

    QByteArray temp = event.toLatin1();
    char* eventChar = temp.data();

    file << timestamp
         << ',' << eventChar
         << ',' << vector.x()
         << ',' << vector.y()
         << ',' << vector.z()
         << std::endl;
}
